#pragma once

#include <sysinfoapi.h>

namespace AYA
{
	namespace Util
	{
		int GetSystemCoreCount()
		{
			SYSTEM_INFO system_info;
			GetSystemInfo(&system_info);
			return (int)system_info.dwNumberOfProcessors;
		}
	}
}