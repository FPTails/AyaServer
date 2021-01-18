#pragma once

#include "../../../Util/Buffer/AyaBuffer.h"
#include "../../Session/SessionObject.h"
#include <queue>
#include <mutex>

namespace AYA
{
	struct JobData
	{
		SessionObject* RecievedSession; 
		Buffer RecievedBuffer;
	};

	class IJobInterface
	{
	public:
		virtual void OnConnect(SessionObject* session) = 0;
		virtual void OnDisconnect(SessionObject* session) = 0;
		virtual void OnMessage(SessionObject* session, Buffer& recieved_buffer) = 0;
		virtual void OnUpdate() = 0;

	public:
		void Update();
		void PushJob(JobData& job_data);

	private:
		bool PopJob(JobData& out_job_data);
		bool IsExistJob();
	private:
		std::queue<JobData> m_job_queue;
		std::mutex m_job_queue_lcok;
	};
}