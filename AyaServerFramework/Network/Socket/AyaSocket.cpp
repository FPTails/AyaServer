#include "stdafx.h"
#include "AyaSocket.h"

namespace AYA
{
	Socket::Socket(SocketOption& socket_option) : 
		m_addr_info(socket_option.IP, socket_option.Port)
	{
		m_recv_bytes = 0;
		m_send_bytes = 0;
		std::memset(m_buffer, 0, sizeof(m_buffer));

		SetSocketOption(socket_option);
	}

	Socket::Socket(short port) :
		m_addr_info(nullptr, port)
	{
		m_recv_bytes = 0;
		m_send_bytes = 0;
		std::memset(m_buffer, 0, sizeof(m_buffer));

		SocketOption socket_option;
		socket_option.IP = nullptr;
		socket_option.Port = port;

		SetSocketOption(socket_option);
	}

	Socket::Socket()
	{
		m_recv_bytes = 0;
		m_send_bytes = 0;
		std::memset(m_buffer, 0, sizeof(m_buffer));
	}

	Socket::~Socket()
	{

	}

	void Socket::SetSocketOption(SocketOption& socket_option)
	{
		if (socket_option.Is_Listen)
		{
			m_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
		}
		else
		{
			m_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
	}

	bool Socket::Send(OverlappedData& overlapped_data)
	{
		u_long bytes_sent = 0;

		int send_result = ::WSASend(m_socket,
			&overlapped_data.WSABuffer,
			1,
			&bytes_sent,
			0,
			(LPOVERLAPPED)&overlapped_data,
			0);

		if ((send_result == SOCKET_ERROR) && (ERROR_IO_PENDING != WSAGetLastError()))
		{
			printf("[에러] WSASend() 함수 실패 : %d\n", WSAGetLastError());
			return false;
		}

		return true;
	}

	bool Socket::Recv(OverlappedData& overlapped_data)
	{
		overlapped_data.WSABuffer.buf = overlapped_data.Buffer.GetBuffer();
		overlapped_data.WSABuffer.len = overlapped_data.Buffer.GetBufferSize();

		DWORD bytes_recvd = 0;
		u_long flags = 0;

		int post_recv_result = ::WSARecv( m_socket,
			&(overlapped_data.WSABuffer),
			1,
			&bytes_recvd,
			&flags,
			(LPOVERLAPPED)&overlapped_data,
			0);


		if (post_recv_result == SOCKET_ERROR && (WSAGetLastError() != ERROR_IO_PENDING))
		{
			printf("[에러] WSARecv()함수 실패 : %d\n", WSAGetLastError());
			return false;
		}

		return true;
	}

	bool Socket::Connect()
	{
		const SOCKADDR_IN& sock_addr_in = m_addr_info.GetAddrIn();

		bool connect_result = connect(m_socket, (SOCKADDR*)&sock_addr_in, sizeof(sock_addr_in));

		return connect_result;
	}

	void Socket::Close(bool is_forced_close)
	{
		struct linger linger_info = { 0,0 };

		linger_info.l_onoff = is_forced_close == true ? 1 : 0;

		shutdown(m_socket, SD_BOTH);

		setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (char*)&linger_info, sizeof(linger_info));

		closesocket(m_socket);

		m_socket = INVALID_SOCKET;
	}
}