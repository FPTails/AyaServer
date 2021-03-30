#pragma once

#include "../../Core/ThreadObject/IAyaJobInterface.h"

namespace AYA
{
	struct ServerInitData
	{
		IJobInterface* Job = nullptr;
		int Job_Thread_Count = 0;
		int Worker_Thread_Count = 0;
		int Max_Client = 0;
		short Port = 0;
		short Udp_Port_Begin = 0;
	};
}
