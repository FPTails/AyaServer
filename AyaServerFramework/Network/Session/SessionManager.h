#pragma once

#include "./SessionObject.h"
#include <memory>
#include <queue>
#include <unordered_map>

namespace AYA
{
	typedef std::queue< std::shared_ptr<SessionObject> > SessionObjectPool;
	typedef std::unordered_map<int, std::shared_ptr<SessionObject>> SessionContainer;

	class SessionObjectManager
	{
	public:
		SessionObjectManager();
		~SessionObjectManager();

	public:
		std::shared_ptr<SessionObject> PopSessionObject();
		void PushSessionObject(std::shared_ptr<SessionObject> overlapped_data);
	private:
		const int DEFAULT_SESSIONK_RESERVE_SIZE = 300;

		void Reserve(int reserve_pool_size);

	private:
		int m_session_index;
		SessionObjectPool m_session_object_pool;

		SessionContainer m_activated_session_container;
	};
}