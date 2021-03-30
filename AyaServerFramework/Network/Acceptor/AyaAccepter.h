#pragma once

#include "../Socket/AyaSocket.h"
#include "../Socket/AyaUdpSocket.h"
#include <unordered_map>
#include "../Session/SessionManager.h"
#include "../../Network/ServerObject/ServerInitData.h"

namespace AYA
{
	class AbstractAsyncResultHandler;

	// Accpet를 하는 클래스. 
	// 해야 하는 것 
	// 1. 기본 사이즈 만큼 미리 Post Accpet를 걸어둔다. 
	// 2. Post Accpet가 완료되면 연결 완료 통지. 

	struct AccepterInitData
	{
		short Port;
		short UdpPortBegin;
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
		bool InitSessionUdpSocket(SessionObject* session_object, short session_udp_port);

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

		std::queue<UdpSocketPotiner> m_udp_socket_queue;
	private:
		short m_port;
		short m_udp_port_begin;
		int m_max_client;
	};
}
