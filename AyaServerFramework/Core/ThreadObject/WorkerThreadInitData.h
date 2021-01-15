#pragma once

#include <winnt.h>

namespace AYA
{
	class IJobInterface;
	class Accepter;

	struct WorkerThreadInitData
	{
		IJobInterface* Job = nullptr;
		HANDLE WorkerThreadHandle = INVALID_HANDLE_VALUE;
		Accepter* _Accepter = nullptr;
		int Worker_Thread_Count = 0;
	};

}