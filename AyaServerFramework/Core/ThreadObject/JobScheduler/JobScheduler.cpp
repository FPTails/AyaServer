#include "JobScheduler.h"

namespace AYA
{
	JobScheduler::JobScheduler()
	{
		m_job = nullptr;
		m_current_write_index = 0;
		m_read_index = 0;
		m_next_write_index = 0;
	}

	JobScheduler::~JobScheduler()
	{

	}

	void JobScheduler::Update()
	{
		if (m_next_write_index == m_read_index)
		{
			return;
		}

		JobData new_job_data;

		if (PopJob(new_job_data))
		{
			m_job->OnMessage(new_job_data.RecievedSession, new_job_data.RecievedBuffer);
		}
	}

	void JobScheduler::PushJob(JobData& job_data)
	{
		int max_job_count = MAX_JOB_COUNT;
		m_current_write_index.compare_exchange_weak(max_job_count, 0);

		auto& current_new_job_data = m_job_array[m_current_write_index.fetch_add(1)];
		current_new_job_data.RecievedSession = job_data.RecievedSession;
		current_new_job_data.RecievedBuffer = job_data.RecievedBuffer;

		m_next_write_index = m_current_write_index.load(std::memory_order_acquire);
		
	}

	bool JobScheduler::PopJob(JobData& out_job_data)
	{
		int max_job_count = MAX_JOB_COUNT;
		m_read_index.compare_exchange_weak(max_job_count, 0);

		auto& poped_job_data = m_job_array[m_read_index.fetch_add(1)];

		out_job_data.RecievedSession = poped_job_data.RecievedSession;
		out_job_data.RecievedBuffer = poped_job_data.RecievedBuffer;

		return true;
	}
}