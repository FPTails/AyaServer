#include "stdafx.h"
#include "AyaUdpSocket.h"

namespace AYA
{
	UdpSocket::UdpSocket(SocketOption& socket_option) :
		m_addr_info(socket_option.IP, socket_option.Port)
	{
		m_recv_bytes = 0;
		m_send_bytes = 0;
		std::memset(m_buffer, 0, sizeof(m_buffer));

		SetSocketOption(socket_option);
	}

	UdpSocket::UdpSocket(short port) :
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

	UdpSocket::UdpSocket()
	{
		m_recv_bytes = 0;
		m_send_bytes = 0;
		std::memset(m_buffer, 0, sizeof(m_buffer));
	}

	UdpSocket::~UdpSocket()
	{

	}

	void UdpSocket::SetSocketOption(SocketOption& socket_option)
	{
		if (socket_option.Is_Listen)
		{
			m_socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, NULL, WSA_FLAG_OVERLAPPED);
		}
		else
		{
			m_socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
	}

	bool UdpSocket::Send(OverlappedData& overlapped_data)
	{
		u_long bytes_sent = 0;
		const SOCKADDR_IN& sock_addr_in = m_addr_info.GetAddrIn();

		int send_result = ::WSASendTo(m_socket,
			&overlapped_data.WSABuffer,
			1,
			&bytes_sent,
			0,
			(SOCKADDR*)&sock_addr_in,
			sizeof(SOCKADDR_IN),
			(LPOVERLAPPED)&overlapped_data,
			NULL);

		if ((send_result == SOCKET_ERROR) && (ERROR_IO_PENDING != WSAGetLastError()))
		{
			printf("[에러] WSASend() 함수 실패 : %d\n", WSAGetLastError());
			return false;
		}

		return true;
	}

	bool UdpSocket::Recv(OverlappedData& overlapped_data)
	{
		overlapped_data.WSABuffer.buf = overlapped_data.Buffer.GetBuffer();
		overlapped_data.WSABuffer.len = overlapped_data.Buffer.GetBufferSize();

		DWORD bytes_recvd = 0;
		u_long flags = 0;
		const SOCKADDR_IN& sock_addr_in = m_addr_info.GetAddrIn();
		int len = sizeof(sock_addr_in);

		int post_recv_result = ::WSARecvFrom(m_socket, 
			&(overlapped_data.WSABuffer), 
			1,
			&bytes_recvd, 
			&flags, 
			(sockaddr*)&sock_addr_in, 
			&len, 
			(LPOVERLAPPED)&overlapped_data, 
			NULL);


		if (post_recv_result == SOCKET_ERROR && (WSAGetLastError() != ERROR_IO_PENDING))
		{
			printf("[에러] WSARecv()함수 실패 : %d\n", WSAGetLastError());
			return false;
		}

		return true;
	}

	bool UdpSocket::Connect()
	{
		/*const SOCKADDR_IN& sock_addr_in = m_addr_info.GetAddrIn();

		bool connect_result = connect(m_socket, (SOCKADDR*)&sock_addr_in, sizeof(sock_addr_in));

		return connect_result;*/

		return true;
	}

	void UdpSocket::Close(bool is_forced_close)
	{
		struct linger linger_info = { 0,0 };

		linger_info.l_onoff = is_forced_close == true ? 1 : 0;

		shutdown(m_socket, SD_BOTH);

		setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (char*)&linger_info, sizeof(linger_info));

		closesocket(m_socket);

		m_socket = INVALID_SOCKET;
	}
}