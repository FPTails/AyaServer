#include "AyaServerObject.h"

namespace AYA
{
	ServerObject::ServerObject()
	{
		m_worker_thread = nullptr;
		m_server_job = nullptr;
		m_accepter = nullptr;
	}

	ServerObject::~ServerObject()
	{

	}

	bool ServerObject::Init(ServerInitData& server_init_data)
	{
		m_worker_thread = server_init_data.WorkerThread;
		m_server_job = server_init_data.ServerJob;
		m_accepter = server_init_data.ServerAccepter;

		return true;
	}

	bool ServerObject::Start()
	{
		if (false == m_accepter->Open())
		{
			false;
		}

		return true;
	}
}