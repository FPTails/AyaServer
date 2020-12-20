#include "SessionManager.h"

namespace AYA
{

	SessionObjectManager::SessionObjectManager()
	{
		m_session_index = 0;
		Reserve(DEFAULT_SESSIONK_RESERVE_SIZE);
	}

	SessionObjectManager::~SessionObjectManager()
	{
		m_session_index = 0;
	}

	std::shared_ptr<SessionObject> SessionObjectManager::PopSessionObject()
	{
		if (m_session_object_pool.empty())
		{
			Reserve(DEFAULT_SESSIONK_RESERVE_SIZE);
		}

		auto front_sesion_object = m_session_object_pool.front();
		m_session_object_pool.pop();

		m_activated_session_container.insert(std::make_pair(front_sesion_object->GetSessionIndex(), front_sesion_object));

		return front_sesion_object;
	}

	void SessionObjectManager::PushSessionObject(std::shared_ptr<SessionObject> session_object)
	{
		if (nullptr == session_object)
		{
			return;
		}

		m_session_object_pool.push(session_object);

		auto activated_session_object_finder = m_activated_session_container.find(session_object->GetSessionIndex());

		if (m_activated_session_container.end() != activated_session_object_finder)
		{
			m_activated_session_container.erase(activated_session_object_finder);
		}
	}

	void SessionObjectManager::Reserve(int reserve_pool_size)
	{
		if (false == m_session_object_pool.empty())
		{
			SessionObjectPool empty_queue;
			std::swap(m_session_object_pool, empty_queue);
		}

		// reserve 시 시작 session index는 현재 나와있는 index 부터 출발한다. 
		int current_session_index = m_session_index;
		int max_session_index = current_session_index + reserve_pool_size;

		for (int i = current_session_index; i < max_session_index; ++i)
		{
			auto new_session_object = std::make_shared<SessionObject>(i);
			m_session_object_pool.push(new_session_object);
			++current_session_index;
		}

		m_session_index = current_session_index;
	}
}