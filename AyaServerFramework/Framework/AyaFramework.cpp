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
		// �⺻ WSADATA �� ȣ��. 
		WSADATA wsa_data;

		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
		{
			// todo. ���߿� �α�.
			int last_error = GetLastError();

			return false;
		} // if 


		// ���� ������ �⵿ ( Accept, Recv, Send �� ���� �� )
		

		// todo . service object ��� ( ���� ���񽺴� �ϳ�, Ŭ���̾�Ʈ ���񽺴� ������. )
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
			// ���� �ؾ��� �� ���. 

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