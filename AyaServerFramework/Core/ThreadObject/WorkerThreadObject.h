#pragma once

#include <WinSock2.h>
#include <list>
#include <thread>

#include <functional>
#include "../Overlapped/OverlappedData.h"
#include "./IoHandler/IOHandler.h"
#include "../../Network/ServerObject/ServerInitData.h"
#include "./WorkerThreadInitData.h"

namespace AYA
{
	class WorkerThreadObject
	{
	public:
		WorkerThreadObject();
		virtual ~WorkerThreadObject();

	public:
		bool Init(WorkerThreadInitData& init_data);
		bool Start();
		void Stop();

		inline const HANDLE& GetCompletionPort() const 
		{ 
			return m_completion_port; 
		}

		inline const bool GetIsRun() const 
		{ 
			return m_is_run; 
		}

		inline IoHandler& GetIOHanlder() { return m_io_handler; }

	private:
		void WorkerThread();

	private:
		HANDLE m_completion_port;
		bool m_is_run;
		std::list<std::thread> m_worker_thread_pool;
		int m_worker_thread_count;
		IoHandler m_io_handler;
	};
}