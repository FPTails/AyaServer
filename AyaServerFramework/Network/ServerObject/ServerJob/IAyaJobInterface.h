#pragma once

#include "../../../Util/Buffer/AyaBuffer.h"
#include "../../Session/SessionObject.h"

namespace AYA
{
	class IJobInterface
	{
	public:
		virtual void OnConnect(SessionObject* session) = 0;
		virtual void OnDisconnect(SessionObject* session) = 0;
		virtual void OnMessage(SessionObject* session, const Buffer& recieved_buffer) = 0;
		virtual void OnUpdate() = 0;
	};
}