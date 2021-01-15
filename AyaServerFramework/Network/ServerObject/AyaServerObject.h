#pragma once

#include "../Acceptor/AyaAccepter.h"
#include "../../Core/ThreadObject/JobThreadObject.h"
#include "../../Core/ThreadObject/WorkerThreadObject.h"
#include "ServerInitData.h"

namespace AYA
{
	// ���� ������Ʈ�� �⺻������ Port �ϳ��� �ϳ� �����ȴ�. 
	// �����Ҷ� �ִ� Ŭ���̾�Ʈ ���� �����ؾ� �Ѵ�. (�̰� ������ Post Accpet�� �Ѵ�.)
	// ���� ������Ʈ�� Accpeter�� ������ �ִ�.
	class ServerObject
	{
	public:
		ServerObject();
		
		bool Init(ServerInitData& server_init_data);
		bool Start();
		~ServerObject();
	private:
		WorkerThreadObject m_worker_thread;
		JobThreadObject m_job_thread;
		Accepter m_accepter;
	};
}

