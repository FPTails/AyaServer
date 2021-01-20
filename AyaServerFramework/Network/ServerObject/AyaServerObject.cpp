#include "AyaServerObject.h"

namespace AYA
{
	ServerObject::ServerObject()
	{
		
	}

	ServerObject::~ServerObject()
	{
		m_worker_thread.Stop();

		m_job_thread.Stop();
	}

	bool ServerObject::Init(ServerInitData& server_init_data)
	{
		m_job_thread.Init(server_init_data);

		WorkerThreadInitData worker_init_data;
		worker_init_data._Accepter = &m_accepter;
		worker_init_data.Job = server_init_data.Job;
		worker_init_data._JobScheduler = &(m_job_thread.GetJobScheduler());
		worker_init_data.Worker_Thread_Count = server_init_data.Worker_Thread_Count;
		m_worker_thread.Init(worker_init_data);

		AccepterInitData accpet_init_data;
		accpet_init_data.Max_Client = server_init_data.Max_Client;
		accpet_init_data.Port = server_init_data.Port;
		accpet_init_data.Worker_Thread_Handle = m_worker_thread.GetCompletionPort();
		m_accepter.Init(accpet_init_data);

		return true;
	}

	bool ServerObject::Start()
	{
		m_worker_thread.Start();
		m_job_thread.Start();

		if (false == m_accepter.Open())
		{
			false;
		}

		return true;
	}
}