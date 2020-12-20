#pragma once

#include "../Acceptor/AyaAccepter.h"
#include "./ServerJob/IAyaJobInterface.h"

namespace AYA
{
	class ServerInitData
	{
	public:
		WorkerThreadObject* WorkerThread;
		IJobInterface* ServerJob;
		Accepter* ServerAccepter;
	};

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
		WorkerThreadObject* m_worker_thread;
		IJobInterface* m_server_job;
		Accepter* m_accepter;
	};
}
