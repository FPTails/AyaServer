#pragma once

#include <list>
#include <thread>
#include "../../Network/ServerObject/ServerInitData.h"
#include "JobScheduler/JobScheduler.h"

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

		inline JobScheduler& GetJobScheduler() { return m_job_scheduler; }
	private:
		void JobThread();

	private:
		JobScheduler m_job_scheduler;
		std::list<std::thread> m_job_thread_pool;
		int m_job_thread_count;
		bool m_is_run;
	};
}