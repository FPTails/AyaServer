#pragma once

#include "../../../Util/Buffer/AyaBuffer.h"
#include "../../../Network/Session/SessionObject.h"
#include <array>
#include <atomic>
#include "../IAyaJobInterface.h"
#include <concurrent_queue.h>

namespace AYA
{
	struct JobData
	{
		SessionObject* RecievedSession = nullptr;
		Buffer RecievedBuffer;
	};

	class JobScheduler
	{
	public:
		static const int MAX_JOB_COUNT = 2048;

		JobScheduler(unsigned short update_milliseconds = 100);
		~JobScheduler();

		void Update();
		void PushJob(JobData& job_data);
		bool IsUpdateTime();
		void DecideNextUpdateTime();
		inline void SetJob(IJobInterface* job) { m_job = job; }
		inline size_t GetCurrentJobCount() { return m_job_queue.unsafe_size(); }
		inline int GetMaxJobIndex() { return MAX_JOB_COUNT - 1; }
	private:
		bool PopJob(JobData& out_job_data);
	private:
		Concurrency::concurrent_queue<JobData> m_job_queue;
		
		IJobInterface* m_job;

		int m_next_update_time;

		const int m_update_elapsed_time;
	};
}