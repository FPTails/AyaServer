#include "stdafx.h"
#include "Util/System/System.h"
#include "JobScheduler.h"


namespace AYA
{
	JobScheduler::JobScheduler(unsigned short update_milliseconds) : m_update_elapsed_time(update_milliseconds)
	{
		m_job = nullptr;

		m_next_update_time = Util::CurrentTimeStamp() + update_milliseconds;
	}

	JobScheduler::~JobScheduler()
	{

	}

	void JobScheduler::Update()
	{
		// ���� ������Ʈ �� ���� �ȵ�. 
		if (false == IsUpdateTime())
		{
			return;
		}

		// ���� ������Ʈ �ð� ����. 
		DecideNextUpdateTime();

		// ������Ʈ �ð��� ������ �� queue�� ��� ����. 
		if (m_job_queue.empty())
		{
			return;
		}

		JobData new_job_data;

		if (PopJob(new_job_data))
		{
			m_job->OnMessage(new_job_data.RecievedSession, new_job_data.RecievedBuffer);
		}
	}

	bool JobScheduler::IsUpdateTime()
	{
		if (Util::CurrentTimeStamp() < m_next_update_time)
		{
			return false;
		}

		return true;
	}

	void JobScheduler::DecideNextUpdateTime()
	{
		m_next_update_time = Util::CurrentTimeStamp() + m_update_elapsed_time;
	}

	void JobScheduler::PushJob(JobData& job_data)
	{
		m_job_queue.push(job_data);	
	}

	bool JobScheduler::PopJob(JobData& out_job_data)
	{
		return m_job_queue.try_pop(out_job_data);
	}
}