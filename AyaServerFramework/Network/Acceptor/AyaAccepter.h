#pragma once

#include "../Socket/AyaSocket.h"
#include <unordered_map>
#include "../Session/SessionManager.h"
#include "../../Core/ThreadObject/ThreadObject.h"

namespace AYA
{
	class AbstractAsyncResultHandler;

	// Accpet를 하는 클래스. 
	// 해야 하는 것 
	// 1. 기본 사이즈 만큼 미리 Post Accpet를 걸어둔다. 
	// 2. Post Accpet가 완료되면 연결 완료 통지. 

	class Accepter
	{
	public:
		Accepter();
		~Accepter();

		inline void SetWorkerThreadCompletionPort(const HANDLE& worker_thread_handle) { m_worker_thread_handle = worker_thread_handle; }
		bool Open();

		bool PostAcceptForSession(SessionObject* session_object);
	public:
		inline short GetPort() { return m_port; }
		inline void SetPort(short port) { m_port = port; }

		inline int GetMaxClient() { return m_max_client; }
		inline void SetMaxClient(int max_client) { m_max_client = max_client; }

	private:
		bool ReservePostAccept(int max_client_count);

		bool BindAndListen(short port);

		bool InitListenCompletionPort();

		std::shared_ptr<SessionObject> PopClientSessionObject();
	private:
		Socket m_listen_socket;
		SessionObjectManager m_session_object_manager;
		HANDLE m_worker_thread_handle;

	private:
		short m_port;
		int m_max_client;
	};
}
