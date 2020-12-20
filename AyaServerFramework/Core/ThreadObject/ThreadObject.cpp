#include "ThreadObject.h"
#include <thread>
#include "../../Network/Session/SessionObject.h"

#include "../../Network/ServerObject/ServerJob/IAyaJobInterface.h"
#include "../../Network/Acceptor/AyaAccepter.h"

namespace AYA
{
	WorkerThreadObject::WorkerThreadObject()
	{
		m_completion_port = INVALID_HANDLE_VALUE;
		m_is_run = false;
		m_job = nullptr;
		m_accepter = nullptr;
	}

	WorkerThreadObject::~WorkerThreadObject()
	{

	}

	void WorkerThreadObject::InitIoHandlerDictionary()
	{
		m_io_handler_dictionary[OVERLAPPED_IO_TYPE::ACCEPT] = &WorkerThreadObject::HandleAccept;
		m_io_handler_dictionary[OVERLAPPED_IO_TYPE::DISCONNECT] = &WorkerThreadObject::HandleDisconnect;
		m_io_handler_dictionary[OVERLAPPED_IO_TYPE::RECV] = &WorkerThreadObject::HandleRecieveMessage;
		m_io_handler_dictionary[OVERLAPPED_IO_TYPE::SEND] = &WorkerThreadObject::HandleSendComplete;
	}

	bool WorkerThreadObject::Start(int thread_count)
	{
		if (0 >= thread_count)
		{
			return false;
		}

		// create io completion port 
		m_completion_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);

		if (INVALID_HANDLE_VALUE == m_completion_port)
		{
			return false;
		}

		InitIoHandlerDictionary();

		m_is_run = true;

		// start thread  loop
		for (int i = 0; i < thread_count; ++i)
		{
			m_thread_pool.emplace_back(std::thread([this]() {WorkerThread(); }));
		} // for 

		return true;
	}

	void WorkerThreadObject::Stop()
	{
		m_is_run = false;

		for (auto& curr_thread : m_thread_pool)
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
			CompletionResultData compeltion_result_data;
			compeltion_result_data.Completion_Result = GetQueuedCompletionStatus(m_completion_port, &compeltion_result_data.Byte_Transferred, &completion_key, &overlapped, INFINITE);
			
			HandleIoData(compeltion_result_data, (OverlappedData*)overlapped);
		} 
	}

	bool WorkerThreadObject::IsDiconnectionCompletion(CompletionResultData& completion_result_data, OverlappedData* per_io_data)
	{
		if (TRUE == completion_result_data.Completion_Result)
		{
			return false;
		}

		if (0 != completion_result_data.Byte_Transferred)
		{
			return false;
		}

		if (OVERLAPPED_IO_TYPE::ACCEPT == per_io_data->IOType)
		{
			return false;
		}

		return true;
	}

	void WorkerThreadObject::HandleIoData(CompletionResultData& completion_result_data, OverlappedData* per_io_data)
	{
		if (nullptr == per_io_data)
		{
			return;
		}

		OVERLAPPED_IO_TYPE io_type = per_io_data->IOType;

		if (IsDiconnectionCompletion(completion_result_data, per_io_data))
		{
			io_type = OVERLAPPED_IO_TYPE::DISCONNECT;
		}

		auto io_hanlder_finder = m_io_handler_dictionary.find(io_type);

		if (m_io_handler_dictionary.end() != io_hanlder_finder)
		{
			auto io_handler = io_hanlder_finder->second;

			(this->*io_handler)(completion_result_data, per_io_data);
		}
	}

	void WorkerThreadObject::HandleAccept(CompletionResultData& completion_result_data, OverlappedData* io_data)
	{
		auto session_object = io_data->SessionObject;
		session_object->OnConnect(m_completion_port);
		m_job->OnConnect(session_object);
	}

	void WorkerThreadObject::HandleDisconnect(CompletionResultData& completion_result_data, OverlappedData* io_data)
	{
		auto session_object = io_data->SessionObject;
		session_object->OnDisConnect();
		
		m_job->OnDisconnect(session_object);
		
		m_accepter->PostAcceptForSession(session_object);
	}

	void WorkerThreadObject::HandleSendComplete(CompletionResultData& completion_result_data, OverlappedData* io_data)
	{
		auto session_object = io_data->SessionObject;
		session_object->OnSendComplete();
	}

	void WorkerThreadObject::HandleRecieveMessage(CompletionResultData& completion_result_data, OverlappedData* io_data)
	{
		auto session_object = io_data->SessionObject;
		session_object->OnRecieve();
		Buffer recieved_buffer(io_data->WSABuffer.buf, completion_result_data.Byte_Transferred);
		m_job->OnMessage(session_object, recieved_buffer);
	}
}

