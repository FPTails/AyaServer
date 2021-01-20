#pragma once

#include "../../Overlapped/OverlappedData.h"
#include <unordered_map>
#include "../WorkerThreadInitData.h"
#include "../JobScheduler/JobScheduler.h"

namespace AYA
{
	class IJobInterface;
	class Accepter;

	struct IORequestData
	{
	public:
		BOOL Completion_Result = FALSE;
		DWORD Byte_Transferred = 0;
	};

	class IoHandler
	{
	public:
		IoHandler();
		virtual ~IoHandler();

		bool Init(WorkerThreadInitData& server_init_data);
	protected:
		virtual void HandleAccept(IORequestData& completion_result_data, OverlappedData* io_data);
		virtual void HandleDisconnect(IORequestData& completion_result_data, OverlappedData* io_data);
		virtual void HandleSendComplete(IORequestData& completion_result_data, OverlappedData* io_data);
		virtual void HandleRecieveMessage(IORequestData& completion_result_data, OverlappedData* io_data);

	public:
		void HandleIoData(IORequestData& completion_result_data, OverlappedData* per_io_data);
		bool IsDiconnectionCompletion(IORequestData& completion_result_data, OverlappedData* per_io_data);

	private:
		void InitIoHandlerDictionary();

	private:
		typedef void (IoHandler::* IOHandlerFunction)(IORequestData& completion_result_data, OverlappedData* io_data);
		std::unordered_map< OVERLAPPED_IO_TYPE, IOHandlerFunction> m_io_handler_dictionary;

	private:
		IJobInterface* m_job;
		HANDLE m_worker_thread_handle;
		Accepter* m_accepter;
		JobScheduler* m_job_scheduler;
	};
}