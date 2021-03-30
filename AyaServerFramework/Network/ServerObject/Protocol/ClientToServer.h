#pragma once

#include <string>
#include "../../../Util/Buffer/AyaBufferStream.h"

namespace Client_To_Server
{
	enum CLIENT_TO_SERVER_PROTOCOL_NUMBER
	{
		CONNECT_NOTIFY,
		LOGIN_REQUEST = 100,
	};

	class PacketHeader
	{
	public:
		int Protocol;
	};

	class ConnectNotify : public PacketHeader
	{
	public:
		short udp_port;

		friend AYA::BufferStream& operator<<(AYA::BufferStream& stream, ConnectNotify& write)
		{
			stream << write.Protocol;
			stream << write.udp_port;

			return stream;
		}

		friend AYA::BufferStream& operator>>(AYA::BufferStream& stream, ConnectNotify& read)
		{
			stream >> read.Protocol;
			stream >> read.udp_port;

			return stream;
		}
	};

	class LoginRequest : public PacketHeader
	{
	public:
		std::wstring Id;
		std::wstring Password;

		friend AYA::BufferStream& operator<<(AYA::BufferStream& stream, LoginRequest& write)
		{
			stream << write.Protocol;
			stream << write.Id;
			stream << write.Password;

			return stream;
		}

		friend AYA::BufferStream& operator>>(AYA::BufferStream& stream, LoginRequest& read)
		{
			stream >> read.Protocol;
			stream >> read.Id;
			stream >> read.Password;

			return stream;
		}
	};
}

