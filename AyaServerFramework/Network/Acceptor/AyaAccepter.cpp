#include "AyaAccepter.h"
#include <MSWSock.h>
#include <WinSock2.h>
#include "../../Core/AsyncHandler/AyaAccpetAsyncResultHandler.h"


namespace AYA
{
	Accepter::Accepter()
	{
		m_worker_thread_handle = nullptr;
		m_port = 0;
		m_max_client = 0;
	}

	bool Accepter::Init(AccepterInitData& accpeter_init_data)
	{
		SetPort(accpeter_init_data.Port);
		SetMaxClient(accpeter_init_data.Max_Client);
		SetWorkerThreadHandle(accpeter_init_data.Worker_Thread_Handle);

		return true;
	}

	bool Accepter::Open()
	{
		SocketOption socket_option;
		socket_option.Port = m_port;
		socket_option.Is_Listen = true;

		m_listen_socket.SetSocketOption(socket_option);

		if (false == BindAndListen(m_port))
		{
			return false;
		}

		if (false == InitListenCompletionPort())
		{
			return false;
		}

		if (false == ReservePostAccept(m_max_client))
		{
			return false;
		}

		return true;
	}

	bool Accepter::InitListenCompletionPort()
	{
		auto iocp_handle = CreateIoCompletionPort((HANDLE)m_listen_socket.GetSocketHandle(), m_worker_thread_handle, (UINT32)0, 0);

		if (NULL == iocp_handle)
		{
			printf("Accpet IO Handle Create Fail \n");
			return false;
		}

		return true;
	}

	Accepter::~Accepter()
	{
		m_listen_socket.Close();
	}

	bool Accepter::BindAndListen(short port)
	{
		const int BACK_LOG_SIZE = 5;

		SOCKADDR_IN server_addrin;
		server_addrin.sin_family = AF_INET;
		server_addrin.sin_port = htons(port);
		server_addrin.sin_addr.s_addr = htonl(INADDR_ANY);

		int bind_result = bind(m_listen_socket.GetSocketHandle(), (SOCKADDR*)&server_addrin, sizeof(SOCKADDR_IN));

		if (0 != bind_result)
		{
			printf("Bind Fail : %d\n", WSAGetLastError());
			return false;
		}

		int listen_result = listen(m_listen_socket.GetSocketHandle(), BACK_LOG_SIZE);

		if (0 != listen_result)
		{
			printf("Listen Fail : %d\n", WSAGetLastError());
			return false;
		}

		return true;
	}

	std::shared_ptr<SessionObject> Accepter::PopClientSessionObject()
	{
		SocketOption socket_option;
		socket_option.Is_Listen = false;

		auto session_object = m_session_object_manager.PopSessionObject();
		auto& session_socket = session_object->GetSocket();
		session_socket.SetSocketOption(socket_option);

		return session_object;
	}

	bool Accepter::ReservePostAccept(int max_client_count)
	{
		for (int i = 0; i < max_client_count; ++i)
		{
			auto session_object = PopClientSessionObject();

			if (false == PostAcceptForSession(session_object.get()))
			{
				printf("AccpetEx Fail : %d\n", WSAGetLastError());
				return false;
			}
		}

		return true;
	}

	bool Accepter::PostAcceptForSession(SessionObject* session_object)
	{
		if (nullptr == session_object)
		{
			return false;
		}

		if (session_object->IsConnected())
		{
			return false;
		}

		const int ADDRIN_API_RESERVED_SIZE = 16;

		DWORD bytes = 0;
		int addr_size = sizeof(SOCKADDR_IN) + ADDRIN_API_RESERVED_SIZE;
		auto session_socket = session_object->GetSocket();
		auto converted_accept_overalpped_data = (LPWSAOVERLAPPED)(session_object->GetAcceptOverlappedData());

		BOOL aceept_result = AcceptEx(m_listen_socket.GetSocketHandle(),
			session_socket.GetSocketHandle(),
			session_socket.GetAccpetedBuffer(),
			0,
			addr_size,
			addr_size,
			&bytes,
			converted_accept_overalpped_data);

		bool is_failed_accept = (FALSE == aceept_result) && (WSA_IO_PENDING != WSAGetLastError());

		if (is_failed_accept)
		{
			printf("AccpetEx Fail : %d\n", WSAGetLastError());
			return false;
		}

		return true;
	}
};