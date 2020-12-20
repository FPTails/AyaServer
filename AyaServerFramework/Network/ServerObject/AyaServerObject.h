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

	// 서버 오브젝트는 기본적으로 Port 하나당 하나 생성된다. 
	// 생성할때 최대 클라이언트 수를 지정해야 한다. (이걸 가지고 Post Accpet를 한다.)
	// 서버 오브젝트는 Accpeter를 가지고 있다.
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
