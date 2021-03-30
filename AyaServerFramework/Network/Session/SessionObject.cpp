#include "stdafx.h"
#include "SessionObject.h"
#include "../Acceptor/AyaAccepter.h"

namespace AYA
{ 
	SessionObject::SessionObject(int session_index) :
		m_session_index(session_index)
	{
		m_is_connected = false;

		InitOverlappedIOData();
	}

	SessionObject::~SessionObject()
	{

	}

	void SessionObject::InitOverlappedIOData()
	{
		m_acceept_overlapped_data = g_OverlappedIOManager->PopOverlappedData(OVERLAPPED_IO_TYPE::ACCEPT);
		m_acceept_overlapped_data->SessionObject = this;

		m_recieve_overlapped_data = g_OverlappedIOManager->PopOverlappedData(OVERLAPPED_IO_TYPE::RECV);
		m_recieve_overlapped_data->SessionObject = this;
		m_recieve_overlapped_data->WSABuffer.buf = m_recieve_overlapped_data->Buffer.GetBuffer();
 		m_recieve_overlapped_data->WSABuffer.len = m_recieve_overlapped_data->Buffer.GetBufferSize();

		m_udp_recieve_overlapped_data = g_OverlappedIOManager->PopOverlappedData(OVERLAPPED_IO_TYPE::RECV_FROM);
		m_udp_recieve_overlapped_data->SessionObject = this;
		m_udp_recieve_overlapped_data->WSABuffer.buf = m_udp_recieve_overlapped_data->Buffer.GetBuffer();
		m_udp_recieve_overlapped_data->WSABuffer.len = m_udp_recieve_overlapped_data->Buffer.GetBufferSize();
	}

	void SessionObject::ReleaseOverlappedIOData()
	{
		g_OverlappedIOManager->PushOverlappedData(m_acceept_overlapped_data);
		g_OverlappedIOManager->PushOverlappedData(m_recieve_overlapped_data);
		g_OverlappedIOManager->PushOverlappedData(m_udp_recieve_overlapped_data);
		
		int curr_queue_count = (int)m_send_queue.size();

		for (int i = 0; i < curr_queue_count; ++i)
		{
			auto& curr_send_data = m_send_queue.front();
			m_send_queue.pop();

			g_OverlappedIOManager->PushOverlappedData(curr_send_data);
		}
	}

	void SessionObject::OnConnect(const HANDLE& connection_thread_handle)
	{
		// tcp 소켓 등록 
		auto returned_handle = CreateIoCompletionPort((HANDLE)m_socket.GetSocketHandle(), connection_thread_handle, (ULONG_PTR)this, 0);

		if (NULL == returned_handle)
		{
			// todo. 에러 처리. 
			printf("SocketBindingFail : %d\n", GetLastError());

			return;
		}

		m_is_connected = true;

		// tcp 수신 대기 상태로 등록한다. 
		m_socket.Recv(*m_recieve_overlapped_data);

		// udp 소켓 등록 
		auto udp_returned_handle = CreateIoCompletionPort((HANDLE)m_udp_socket.GetSocketHandle(), connection_thread_handle, (ULONG_PTR)this, 0);

		if (NULL == udp_returned_handle)
		{
			// todo. 에러 처리. 
			printf("UdpSocketBindingFail : %d\n", GetLastError());
			return;
		}

		m_udp_socket.Recv(*m_udp_recieve_overlapped_data);
	}

	void SessionObject::OnDisConnect()
	{
		m_socket.Close();

		SocketOption socket_option;
		socket_option.Is_Listen = false;

		m_socket.SetSocketOption(socket_option);

		m_is_connected = false;

		m_udp_socket.Close();
	}

	void SessionObject::OnRecieve()
	{
		m_socket.Recv(*m_recieve_overlapped_data);
	}

	void SessionObject::OnRecieveFrom()
	{
		m_udp_socket.Recv(*m_recieve_overlapped_data);
	}

	void SessionObject::OnSendComplete()
	{
		std::lock_guard<std::mutex> guard(m_send_queue_lock);

		if (m_send_queue.empty())
		{
			return;
		}

		g_OverlappedIOManager->PushOverlappedData(m_send_queue.front());
		m_send_queue.pop();

		SendIo();
	}

	bool SessionObject::Send(Buffer& buffer)
	{
		std::lock_guard<std::mutex> guard(m_send_queue_lock);

		auto new_send_data = g_OverlappedIOManager->PopOverlappedData(OVERLAPPED_IO_TYPE::SEND);
		new_send_data->SessionObject = this;
		new_send_data->Buffer.Copy(buffer);
		new_send_data->WSABuffer.buf = new_send_data->Buffer.GetBuffer();
		new_send_data->WSABuffer.len = new_send_data->Buffer.GetBufferSize();
		new_send_data->IsTcp = true;

		m_send_queue.push(new_send_data);

		bool is_send_emmidiately = 1 == m_send_queue.size();

		if (is_send_emmidiately)
		{
			return SendIo();
		}

		return true;
	}

	bool SessionObject::SendTo(Buffer& buffer)
	{
		std::lock_guard<std::mutex> guard(m_send_queue_lock);

		auto new_send_data = g_OverlappedIOManager->PopOverlappedData(OVERLAPPED_IO_TYPE::SEND_TO);
		new_send_data->SessionObject = this;
		new_send_data->Buffer.Copy(buffer);
		new_send_data->WSABuffer.buf = new_send_data->Buffer.GetBuffer();
		new_send_data->WSABuffer.len = new_send_data->Buffer.GetBufferSize();
		new_send_data->IsTcp = false;

		m_send_queue.push(new_send_data);

		bool is_send_emmidiately = 1 == m_send_queue.size();

		if (is_send_emmidiately)
		{
			return SendIo();
		}

		return true;
	}

	bool SessionObject::SendIo()
	{
		if (m_send_queue.empty())
		{
			return false;
		}

		auto send_io_data = m_send_queue.front();

		if (send_io_data->IsTcp)
		{
			m_socket.Send(*send_io_data);
			return true;
		}

		m_udp_socket.Send(*send_io_data);
		return true;
	}
}