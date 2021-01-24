#pragma once

#include <unordered_map>
#include "./UserObject.h"
#include <queue>
#include <mutex>


typedef std::queue <UserObjectSmartPointer> UserObjectMemoryPoolList;
typedef std::unordered_map<USERKEY, UserObjectSmartPointer> UserKeyCachingUserObjectDictionary;
typedef std::unordered_map<SESSIONKEY, UserObjectSmartPointer> SessionKeyCachingUserObjectDictionary;

class UserManager
{
public:
	UserManager();
	~UserManager();

	UserObjectSmartPointer CreateUserOnSessionConnect(SESSIONKEY session_key);
	bool UserLogin(UserLoginData& login_data);
	void ReleaseUserOnSessionDisconnect(SESSIONKEY session_key);

	UserObjectSmartPointer FindUserByUserKey(USERKEY user_key);
	UserObjectSmartPointer FindUserBySessionKey(SESSIONKEY session_key);

	
private:
	UserObjectSmartPointer PopUserObject();
	void PushUserObject(UserObjectSmartPointer released_user_object);

	bool CachingUserKeyDictionary(UserObjectSmartPointer new_user_object);
	bool UnCachingUserKeyDictionary(UserObjectSmartPointer released_user_object);

	bool CachingSessionKeyDictionary(UserObjectSmartPointer new_user_object);
	bool UnCachingSessionKeyDictionary(UserObjectSmartPointer released_user_object);

private:
	UserObjectMemoryPoolList m_userobject_memory_pool;
	std::mutex m_userobject_memorypool_lock;

	UserKeyCachingUserObjectDictionary m_userkey_caching_dictionary;
	std::mutex m_userkey_caching_dictionary_memorypool_lock;

	SessionKeyCachingUserObjectDictionary m_sessionkey_caching_dictionary;
	std::mutex m_sessionkey_caching_dictionary_memorypool_lock;
};