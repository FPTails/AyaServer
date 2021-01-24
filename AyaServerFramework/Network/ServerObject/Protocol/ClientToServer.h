#pragma once

#include <string>
#include "../../../Util/Buffer/AyaBufferStream.h"

namespace Client_To_Server
{
	enum CLIENT_TO_SERVER_PROTOCOL_NUMBER
	{
		LOGIN_REQUEST = 0,
	};

	class PacketHeader
	{
	public:
		int Protocol;
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

