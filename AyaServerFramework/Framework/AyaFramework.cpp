#include "AyaFramework.h"

#include <thread>
#include <process.h>
#include <stdlib.h>
#include <winsock2.h>
#include <MSWSock.h>
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

		m_server_object.Start();

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
		const int DEFAULT_JOB_THREAD_COUNT = 1;

		ServerInitData server_init_data;
		server_init_data.Job = new GameServerJob();
		server_init_data.Job_Thread_Count = DEFAULT_JOB_THREAD_COUNT;
		server_init_data.Max_Client =  DEFAULT_FRAMEWORK_MAX_CLIENT;
		server_init_data.Port = DEFAULT_FRAMEWORK_PORT;
		server_init_data.Worker_Thread_Count = Util::GetSystemCoreCount() * 2;

		m_server_object.Init(server_init_data);
	}
};