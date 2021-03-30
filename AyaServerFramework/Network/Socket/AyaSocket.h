#pragma once

#include "../AddrIn/AyaAddrin.h"
#include "../../Core/Overlapped/OverlappedData.h"
#include "SocketOption.h"

namespace AYA
{
	class Socket
	{
	public:
		Socket();
		Socket(SocketOption& socket_option);
		Socket(short port);
		virtual ~Socket();

	public:
		void SetSocketOption(SocketOption& socket_option);
		bool Send(OverlappedData& overlapped_data);
		bool Recv(OverlappedData& overlapped_data);
		bool Connect();
		void Close(bool is_forced_close = false);

	public:
		inline const SOCKET& GetSocketHandle() const { return m_socket; }
		inline char* GetAccpetedBuffer() { return m_accpeted_buffer; }
	private:
		AddrInfo m_addr_info;
		SOCKET m_socket;
		int m_recv_bytes;
		int m_send_bytes;
		char m_buffer[1024];
		char m_accpeted_buffer[64];
	};

	using SocketPotiner = std::shared_ptr<Socket>;
}