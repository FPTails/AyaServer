#include "IAyaJobInterface.h"

namespace AYA
{
	void IJobInterface::Update()
	{
		if (IsExistJob())
		{
			// job 
			JobData new_job_data;
			PopJob(new_job_data);
			OnMessage(new_job_data.RecievedSession, new_job_data.RecievedBuffer);
		}

		// update 
		OnUpdate();
	}

	bool IJobInterface::IsExistJob()
	{
		std::lock_guard<std::mutex> job_queue_lock_guard(m_job_queue_lcok);

		return m_job_queue.empty() == false;
	}

	void IJobInterface::PushJob(JobData& job_data)
	{
		std::lock_guard<std::mutex> job_queue_lock_guard(m_job_queue_lcok);

		m_job_queue.push(job_data);
	}

	bool IJobInterface::PopJob(JobData& out_job_data)
	{
		std::lock_guard<std::mutex> job_queue_lock_guard(m_job_queue_lcok);

		if (m_job_queue.empty())
		{
			return false;
		}

		auto poped_job_data = m_job_queue.front();
		m_job_queue.pop();

		out_job_data.RecievedSession = poped_job_data.RecievedSession;
		out_job_data.RecievedBuffer.Copy(poped_job_data.RecievedBuffer);

		return true;
	}
}