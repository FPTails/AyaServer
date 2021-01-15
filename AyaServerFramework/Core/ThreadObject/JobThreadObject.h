#pragma once

#include <list>
#include <thread>
#include "../../Network/ServerObject/ServerInitData.h"

namespace AYA
{
	class IJobInterface;

	class JobThreadObject
	{
	public:
		JobThreadObject();
		~JobThreadObject();

	public:
		bool Init(ServerInitData& init_data);
		bool Start();
		bool Stop();

		inline IJobInterface* GetJob() { return m_job; }
	private:
		void JobThread();

	private:
		IJobInterface* m_job;
		std::list<std::thread> m_job_thread_pool;
		int m_job_thread_count;
		bool m_is_run;
	};
}