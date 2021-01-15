#include "JobThreadObject.h"
#include "../../Network/ServerObject/ServerJob/IAyaJobInterface.h"

namespace AYA
{
	JobThreadObject::JobThreadObject()
	{
		m_job = nullptr;
		m_is_run = false;
		m_job_thread_count = 0;
	}

	JobThreadObject::~JobThreadObject()
	{
		
	}

	bool JobThreadObject::Init(ServerInitData& init_data)
	{
		if (nullptr == init_data.Job)
		{
			return false;
		}

		if (nullptr != m_job)
		{
			return false;
		}

		m_job = init_data.Job;

		m_job_thread_count = init_data.Job_Thread_Count;

		return true;
	}


	bool JobThreadObject::Start()
	{
		for (int i = 0; i < m_job_thread_count; ++i)
		{
			m_job_thread_pool.emplace_back(std::thread([this]() {JobThread(); }));
		} // for 

		m_is_run = true;

		return true;
	}

	bool JobThreadObject::Stop()
	{
		m_is_run = false;

		for (auto& job_thread : m_job_thread_pool)
		{
			if (job_thread.joinable())
			{
				job_thread.join();
			}
		}

		return true;
	}

	void JobThreadObject::JobThread()
	{
		while (m_is_run)
		{
			m_job->Update();
		}
	}
}