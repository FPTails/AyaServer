#include "AyaAddrin.h"
#include <Ws2def.h>
#include <WS2tcpip.h>

namespace AYA
{
	AddrInfo::AddrInfo(const char* str_ip_address, short port)
	{
		memset(&m_addr_in, 0, sizeof(SOCKADDR_IN));
		Set(str_ip_address, port);
	}

	AddrInfo::AddrInfo()
	{
		memset(&m_addr_in, 0, sizeof(SOCKADDR_IN));
	}

	AddrInfo::~AddrInfo()
	{

	}

	void AddrInfo::Set(const char* str_ip_address, short port)
	{
		m_addr_in.sin_family = AF_INET;
		m_addr_in.sin_port = htons(port);

		// address 가 null 이면 accept용 초기화. 
		if (NULL == str_ip_address)
		{
			m_addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
		}
		else
		{
			m_addr_in.sin_addr.s_addr = inet_addr(str_ip_address);
		}
	}
}