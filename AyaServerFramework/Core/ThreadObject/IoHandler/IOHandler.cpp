#include "stdafx.h"
#include "IOHandler.h"
#include "../../../Network/Session/SessionObject.h"
#include "../../../Network/Acceptor/AyaAccepter.h"


namespace AYA
{
	IoHandler::IoHandler()
	{
		m_job_scheduler = nullptr;
		m_job = nullptr;
		m_accepter = nullptr;
		m_worker_thread_handle = INVALID_HANDLE_VALUE;
	}

	IoHandler::~IoHandler()
	{

	}

	bool IoHandler::Init(WorkerThreadInitData& server_init_data)
	{
		m_job = server_init_data.Job;
		m_job_scheduler = server_init_data._JobScheduler;
		m_accepter = server_init_data._Accepter;
		m_worker_thread_handle = server_init_data.WorkerThreadHandle;

		InitIoHandlerDictionary();

		return true;
	}

	void IoHandler::InitIoHandlerDictionary()
	{
		m_io_handler_dictionary[OVERLAPPED_IO_TYPE::ACCEPT] = &IoHandler::HandleAccept;
		m_io_handler_dictionary[OVERLAPPED_IO_TYPE::DISCONNECT] = &IoHandler::HandleDisconnect;
		m_io_handler_dictionary[OVERLAPPED_IO_TYPE::RECV] = &IoHandler::HandleRecieveMessage;
		m_io_handler_dictionary[OVERLAPPED_IO_TYPE::SEND] = &IoHandler::HandleSendComplete;
		m_io_handler_dictionary[OVERLAPPED_IO_TYPE::RECV_FROM] = &IoHandler::HandleRecieveFromMessage;
		m_io_handler_dictionary[OVERLAPPED_IO_TYPE::SEND_TO] = &IoHandler::HandleSendToComplete;
	}

	bool IoHandler::IsDiconnectionCompletion(IORequestData& completion_result_data, OverlappedData* per_io_data)
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

	void IoHandler::HandleIoData(IORequestData& completion_result_data, OverlappedData* per_io_data)
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

		if (m_io_handler_dictionary.end() == io_hanlder_finder)
		{
			return;
		}

		auto io_handler = io_hanlder_finder->second;
		(this->*io_handler)(completion_result_data, per_io_data);
	}

	void IoHandler::HandleAccept(IORequestData& completion_result_data, OverlappedData* io_data)
	{
		auto session_object = io_data->SessionObject;
		session_object->OnConnect(m_worker_thread_handle);
		m_job->OnConnect(session_object);
	}

	void IoHandler::HandleDisconnect(IORequestData& completion_result_data, OverlappedData* io_data)
	{
		auto session_object = io_data->SessionObject;

		m_job->OnDisconnect(session_object);
		session_object->OnDisConnect();
		m_accepter->PostAcceptForSession(session_object);
	}

	void IoHandler::HandleSendComplete(IORequestData& completion_result_data, OverlappedData* io_data)
	{
		auto session_object = io_data->SessionObject;
		session_object->OnSendComplete();
	}

	void IoHandler::HandleRecieveMessage(IORequestData& completion_result_data, OverlappedData* io_data)
	{
		auto session_object = io_data->SessionObject;
		Buffer recieved_buffer(io_data->WSABuffer.buf, completion_result_data.Byte_Transferred);

		JobData job_data;
		job_data.RecievedBuffer = recieved_buffer;
		job_data.RecievedSession = session_object;
		m_job_scheduler->PushJob(job_data);

		session_object->OnRecieve();
	}

	void IoHandler::HandleSendToComplete(IORequestData& completion_result_data, OverlappedData* io_data)
	{
		auto session_object = io_data->SessionObject;
		session_object->OnSendComplete();
	}

	void IoHandler::HandleRecieveFromMessage(IORequestData& completion_result_data, OverlappedData* io_data)
	{
		auto session_object = io_data->SessionObject;
		Buffer recieved_buffer(io_data->WSABuffer.buf, completion_result_data.Byte_Transferred);

		JobData job_data;
		job_data.RecievedBuffer = recieved_buffer;
		job_data.RecievedSession = session_object;
		m_job_scheduler->PushJob(job_data);

		session_object->OnRecieveFrom();
	}
}