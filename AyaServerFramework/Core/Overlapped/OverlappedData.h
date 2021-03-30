#pragma once

#include <WinSock2.h>
#include "../../Util/Buffer/AyaBuffer.h"

namespace AYA
{
	enum class OVERLAPPED_IO_TYPE
	{
		NONE = 0,
		ACCEPT,
		SEND,
		RECV,
		DISCONNECT,
		RECV_FROM,
		SEND_TO,
	};

	class SessionObject;

	struct OverlappedData
	{
		OVERLAPPED WSAOverlapped;
		WSABUF WSABuffer;
		OVERLAPPED_IO_TYPE IOType;
		SessionObject* SessionObject;
		Buffer Buffer;
		bool IsTcp;
	};
}