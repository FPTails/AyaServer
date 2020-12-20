#include "AyaFramework.h"

#include <thread>
#include <process.h>
#include <stdlib.h>
#include <winsock2.h>
#include <MSWSock.h>
#include "../Core/AsyncHandler/AyaAbstractAsyncResultHandler.h"
#include "../Network/ServerObject/ServerJob/GameServerJob.h"
#include "../Util/System/System.h"

namespace AYA
{
	Framework::Framework()
	{
		m_is_run = false;
	}

	Framework::~Framework()
	{

	}

	bool Framework::Init(const FrameworkInfo& frame_work_info)
	{
		// 기본 WSADATA 를 호출. 
		WSADATA wsa_data;

		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
		{
			// todo. 나중에 로깅.
			int last_error = GetLastError();

			return false;
		} // if 


		// 메인 쓰레드 기동 ( Accept, Recv, Send 를 위한 것 )
		

		// todo . service object 등록 ( 서버 서비스는 하나, 클라이언트 서비스는 여러개. )
		InitServerObject();

		return true;
	}

	bool Framework::Start()
	{
		printf("SERVER START");

		m_is_run = true;

		while (m_is_run)
		{
			// 뭔가 해야할 일 기술. 

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		return true;
	}

	void Framework::InitServerObject()
	{
		const int DEFAULT_FRAMEWORK_MAX_CLIENT = 1;
		const int DEFAULT_FRAMEWORK_PORT = 11021;

		ServerInitData server_init_data;
		server_init_data.WorkerThread = new WorkerThreadObject();
		server_init_data.ServerAccepter = new Accepter();
		server_init_data.ServerJob = new GameServerJob();

		server_init_data.WorkerThread->Start(Util::GetSystemCoreCount() * 2);
		server_init_data.WorkerThread->SetJob(server_init_data.ServerJob);
		server_init_data.WorkerThread->SetAccepter(server_init_data.ServerAccepter);

		server_init_data.ServerAccepter->SetMaxClient(DEFAULT_FRAMEWORK_MAX_CLIENT);
		server_init_data.ServerAccepter->SetPort(DEFAULT_FRAMEWORK_PORT);
		server_init_data.ServerAccepter->SetWorkerThreadCompletionPort(server_init_data.WorkerThread->GetCompletionPort());

		m_server_object.Init(server_init_data);
		m_server_object.Start();

	}
};