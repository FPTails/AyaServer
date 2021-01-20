#pragma once

#include "../../../Util/Buffer/AyaBuffer.h"
#include "../../../Network/Session/SessionObject.h"
#include <array>
#include <atomic>
#include "../IAyaJobInterface.h"

namespace AYA
{
	const int MAX_JOB_COUNT = 2048;

	struct JobData
	{
		SessionObject* RecievedSession = nullptr;
		Buffer RecievedBuffer;
	};

	class JobScheduler
	{
	public:
		JobScheduler();
		~JobScheduler();

		void Update();
		void PushJob(JobData& job_data);
		inline void SetJob(IJobInterface* job) { m_job = job; }
	private:
		bool PopJob(JobData& out_job_data);
	private:
		std::array<JobData, MAX_JOB_COUNT> m_job_array;
		std::atomic<int> m_current_write_index;
		std::atomic<int> m_read_index;
		std::atomic<int> m_next_write_index;
		IJobInterface* m_job;
	};
}