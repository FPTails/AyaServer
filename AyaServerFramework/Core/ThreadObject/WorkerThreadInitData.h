#pragma once

#include <winnt.h>

namespace AYA
{
	class IJobInterface;
	class Accepter;
	class JobScheduler;

	struct WorkerThreadInitData
	{
		IJobInterface* Job = nullptr;
		HANDLE WorkerThreadHandle = INVALID_HANDLE_VALUE;
		Accepter* _Accepter = nullptr;
		JobScheduler* _JobScheduler = nullptr;
		int Worker_Thread_Count = 0;
	};

}