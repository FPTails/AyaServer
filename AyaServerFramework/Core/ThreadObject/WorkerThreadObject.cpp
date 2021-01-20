#include "WorkerThreadObject.h"
#include <thread>
#include "../../Network/Session/SessionObject.h"

namespace AYA
{
	WorkerThreadObject::WorkerThreadObject()
	{
		m_completion_port = INVALID_HANDLE_VALUE;
		m_is_run = false;
		m_worker_thread_count = 0;
	}

	WorkerThreadObject::~WorkerThreadObject()
	{

	}

	bool WorkerThreadObject::Init(WorkerThreadInitData& init_data)
	{
		// create io completion port 
		m_completion_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);

		if (INVALID_HANDLE_VALUE == m_completion_port)
		{
			return false;
		}

		m_worker_thread_count = init_data.Worker_Thread_Count;
		init_data.WorkerThreadHandle = m_completion_port;

		return m_io_handler.Init(init_data);
	}

	bool WorkerThreadObject::Start()
	{
		if (0 >= m_worker_thread_count)
		{
			return false;
		}

		m_is_run = true;

		// start thread  loop
		for (int i = 0; i < m_worker_thread_count; ++i)
		{
			m_worker_thread_pool.emplace_back(std::thread([this]() {WorkerThread(); }));
		} // for 

		return true;
	}

	void WorkerThreadObject::Stop()
	{
		m_is_run = false;

		for (auto& curr_thread : m_worker_thread_pool)
		{
			if (curr_thread.joinable())
			{
				curr_thread.join();
			}
		}
	}

	void WorkerThreadObject::WorkerThread()
	{
		unsigned __int64 completion_key = 0;

		LPOVERLAPPED overlapped = nullptr;

		DWORD flag = 0;

		while (m_is_run)
		{
			IORequestData compeltion_result_data;
			compeltion_result_data.Completion_Result = GetQueuedCompletionStatus(m_completion_port, &compeltion_result_data.Byte_Transferred, &completion_key, &overlapped, INFINITE);
			
			m_io_handler.HandleIoData(compeltion_result_data, (OverlappedData*)overlapped);
		} 
	}
}

