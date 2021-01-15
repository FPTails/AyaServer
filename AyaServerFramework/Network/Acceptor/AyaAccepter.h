#pragma once

#include "../Socket/AyaSocket.h"
#include <unordered_map>
#include "../Session/SessionManager.h"
#include "../../Network/ServerObject/ServerInitData.h"

namespace AYA
{
	class AbstractAsyncResultHandler;

	// Accpet�� �ϴ� Ŭ����. 
	// �ؾ� �ϴ� �� 
	// 1. �⺻ ������ ��ŭ �̸� Post Accpet�� �ɾ�д�. 
	// 2. Post Accpet�� �Ϸ�Ǹ� ���� �Ϸ� ����. 

	struct AccepterInitData
	{
		short Port;
		int Max_Client;
		HANDLE Worker_Thread_Handle;
	};

	class Accepter
	{
	public:
		Accepter();
		~Accepter();
		
		bool Open();
		bool Init(AccepterInitData& accpeter_init_data);
		bool PostAcceptForSession(SessionObject* session_object);
	public:
		inline short GetPort() { return m_port; }
		inline int GetMaxClient() { return m_max_client; }

	private:
		inline void SetWorkerThreadHandle(const HANDLE& worker_thread_handle) { m_worker_thread_handle = worker_thread_handle; }
		inline void SetPort(short port) { m_port = port; }
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
