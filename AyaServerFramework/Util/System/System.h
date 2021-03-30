#pragma once

namespace AYA
{
	namespace Util
	{
		inline int GetSystemCoreCount()
		{
			SYSTEM_INFO system_info;
			GetSystemInfo(&system_info);
			return (int)system_info.dwNumberOfProcessors;
		}

		inline int CurrentTimeStamp()
		{
			time_t curr_time;

			time(&curr_time);

			return (int)curr_time;
		}
	}
}