#pragma once

#include "../../Util/Buffer/AyaBuffer.h"
#include "../../Network/Session/SessionObject.h"

#include <queue>
#include <atomic>

namespace AYA
{
	class IJobInterface
	{
	public:
		virtual void OnConnect(SessionObject* session) = 0;
		virtual void OnDisconnect(SessionObject* session) = 0;
		virtual void OnMessage(SessionObject* session, Buffer& recieved_buffer) = 0;
		virtual void OnUpdate() = 0;
	};
}