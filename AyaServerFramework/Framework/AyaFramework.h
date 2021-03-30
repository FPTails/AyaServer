#pragma once

#include "./AyaFrameworkInfo.h"
#include "../Network/ServerObject/AyaServerObject.h"

namespace AYA
{
	class Framework
	{
	public:
		Framework();
		virtual ~Framework();

	public:
		bool Init(const FrameworkInfo& frame_work_info);

		bool Start();

	private:
		void InitServerObject();

	private:
		bool m_is_run;

	private:
		ServerObject m_server_object;
	};
}