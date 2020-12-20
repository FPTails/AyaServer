#pragma once

#include <WinSock2.h>
#include <list>
#include <thread>
#include <unordered_map>
#include <functional>
#include "../Overlapped/OverlappedData.h"

namespace AYA
{
	class IJobInterface;

	class Accepter;

	class CompletionResultData
	{
	public:
		BOOL Completion_Result = FALSE;
		DWORD Byte_Transferred = 0;
	};

	class WorkerThreadObject
	{
	public:
		WorkerThreadObject();
		virtual ~WorkerThreadObject();

	public:
		bool Start(int thread_count);
		void Stop();

		inline const HANDLE& GetCompletionPort() const 
		{ 
			return m_completion_port; 
		}

		inline const bool GetIsRun() const 
		{ 
			return m_is_run; 
		}

		inline void SetJob(IJobInterface* job) 
		{ 
			m_job = job; 
		}

		inline void SetAccepter(Accepter* accepter) 
		{ 
			m_accepter = accepter; 
		}

	private:
		void WorkerThread();

		void HandleIoData(CompletionResultData& completion_result_data, OverlappedData* per_io_data);
		bool IsDiconnectionCompletion(CompletionResultData& completion_result_data, OverlappedData* per_io_data);

		void InitIoHandlerDictionary();
	private:
		void HandleAccept(CompletionResultData& completion_result_data, OverlappedData* io_data);
		void HandleDisconnect(CompletionResultData& completion_result_data, OverlappedData* io_data);
		void HandleSendComplete(CompletionResultData& completion_result_data, OverlappedData* io_data);
		void HandleRecieveMessage(CompletionResultData& completion_result_data, OverlappedData* io_data);
	private:
		HANDLE m_completion_port;
		bool m_is_run;
		std::list<std::thread> m_thread_pool;
		IJobInterface* m_job;
		Accepter* m_accepter;

		typedef void (WorkerThreadObject::* IOHandlerFunction)(CompletionResultData& completion_result_data, OverlappedData* io_data);
		std::unordered_map< OVERLAPPED_IO_TYPE, IOHandlerFunction> m_io_handler_dictionary;
	};
}