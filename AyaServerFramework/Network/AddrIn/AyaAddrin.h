#pragma once

#include <WinSock2.h>

namespace AYA
{
	class AddrInfo
	{
	public:
		AddrInfo(const char* str_ip_address, short port);
		AddrInfo();
		virtual ~AddrInfo();

		void Set(const char* str_ip_address, short port);

		const SOCKADDR_IN& GetAddrIn() { return m_addr_in; }
	private:
		SOCKADDR_IN m_addr_in;
	};
}
