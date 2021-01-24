#include "UserManager.h"

UserManager::UserManager()
{

}
UserManager::~UserManager()
{
	m_userkey_caching_dictionary.clear();
	m_sessionkey_caching_dictionary.clear();
	

}

UserObjectSmartPointer UserManager::CreateUserOnSessionConnect(SESSIONKEY session_key)
{
	auto new_user_object_pointer = PopUserObject();
	
	CachingSessionKeyDictionary(new_user_object_pointer);
	
	return new_user_object_pointer;
}

bool UserManager::UserLogin(UserLoginData& login_data)
{
	auto finded_user_object = FindUserBySessionKey(login_data.SessionKey);

	if (nullptr == finded_user_object)
	{
		return false;
	}

	if (false == finded_user_object->Login(login_data))
	{
		return false;
	}

	CachingUserKeyDictionary(finded_user_object);

	return true;
}

UserObjectSmartPointer UserManager::PopUserObject()
{
	std::lock_guard<std::mutex> memory_pool_lock(m_userobject_memorypool_lock);

	if (m_userobject_memory_pool.empty())
	{
		auto new_user_object = std::make_shared<UserObject>();

		if (nullptr == new_user_object)
		{
			return nullptr;
		}

		return new_user_object;
	}
	
	auto caching_user_object_pointer = m_userobject_memory_pool.front();

	m_userobject_memory_pool.pop();

	return caching_user_object_pointer;
}

void UserManager::PushUserObject(UserObjectSmartPointer released_user_object_pointer)
{
	std::lock_guard<std::mutex> memory_pool_lock(m_userobject_memorypool_lock);

	
	m_userobject_memory_pool.push(released_user_object_pointer);
}

void UserManager::ReleaseUserOnSessionDisconnect(SESSIONKEY session_key)
{
	auto user_object = FindUserBySessionKey(session_key);

	UnCachingUserKeyDictionary(user_object);
	UnCachingSessionKeyDictionary(user_object);

	user_object->ClearAtDisconnect();
	PushUserObject(user_object);
}

UserObjectSmartPointer UserManager::FindUserByUserKey(USERKEY user_key)
{
	std::lock_guard<std::mutex> userkey_caching_dic_lock(m_userkey_caching_dictionary_memorypool_lock);

	auto userkey_caching_finder = m_userkey_caching_dictionary.find(user_key);

	if (m_userkey_caching_dictionary.end() == userkey_caching_finder)
	{
		return nullptr;
	}

	return (*userkey_caching_finder).second;
}

UserObjectSmartPointer UserManager::FindUserBySessionKey(SESSIONKEY session_key)
{
	std::lock_guard<std::mutex> sessionkey_caching_dic_lock(m_sessionkey_caching_dictionary_memorypool_lock);

	auto sessionkey_caching_finder = m_sessionkey_caching_dictionary.find(session_key);

	if (m_sessionkey_caching_dictionary.end() == sessionkey_caching_finder)
	{
		return nullptr;
	}

	return (*sessionkey_caching_finder).second;
}

bool UserManager::CachingUserKeyDictionary(UserObjectSmartPointer new_user_object)
{
	std::lock_guard<std::mutex> userkey_caching_dic_lock(m_userkey_caching_dictionary_memorypool_lock);

	if (nullptr == new_user_object)
	{
		return false;
	}

	auto userkey_caching_finder = m_userkey_caching_dictionary.find(new_user_object->GetUserKey());

	if (m_userkey_caching_dictionary.end() != userkey_caching_finder)
	{
		return false;
	}

	m_userkey_caching_dictionary[new_user_object->GetUserKey()] = new_user_object;

	return true;
}

bool UserManager::CachingSessionKeyDictionary(UserObjectSmartPointer new_user_object)
{
	std::lock_guard<std::mutex> sessionkey_caching_dic_lock(m_sessionkey_caching_dictionary_memorypool_lock);

	if (nullptr == new_user_object)
	{
		return false;
	}

	auto sessionkey_caching_finder = m_sessionkey_caching_dictionary.find(new_user_object->GetSessionKey());

	if (m_sessionkey_caching_dictionary.end() != sessionkey_caching_finder)
	{
		return false;
	}

	m_sessionkey_caching_dictionary[new_user_object->GetSessionKey()] = new_user_object;

	return true;
}

bool UserManager::UnCachingUserKeyDictionary(UserObjectSmartPointer released_user_object)
{
	std::lock_guard<std::mutex> userkey_caching_dic_lock(m_userkey_caching_dictionary_memorypool_lock);

	if (nullptr == released_user_object)
	{
		return false;
	}

	auto userkey_caching_finder = m_userkey_caching_dictionary.find(released_user_object->GetUserKey());

	if (m_userkey_caching_dictionary.end() == userkey_caching_finder)
	{
		return false;
	}

	m_userkey_caching_dictionary.erase(userkey_caching_finder);

	return true;

}

bool UserManager::UnCachingSessionKeyDictionary(UserObjectSmartPointer released_user_object)
{
	std::lock_guard<std::mutex> sessionkey_caching_dic_lock(m_sessionkey_caching_dictionary_memorypool_lock);

	if (nullptr == released_user_object)
	{
		return false;
	}

	auto sessionkey_caching_finder = m_sessionkey_caching_dictionary.find(released_user_object->GetSessionKey());

	if (m_sessionkey_caching_dictionary.end() == sessionkey_caching_finder)
	{
		return false;
	}

	m_sessionkey_caching_dictionary.erase(sessionkey_caching_finder);

	return true;
}