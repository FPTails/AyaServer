#pragma once

#include "../Singleton/Singleton.h"
#include <mutex>
#include <list>

namespace AYA
{
	// Logger Class는 일정 주기마다 Update를 호출해줘야 한다. 
	// 주기는 사용자의 기호에 따라 느릴수도 , 빠를수도 있다.
	// 단, Update는 하나의 쓰레드에서만 호출해야 한다. 여러쓰레드가 호출할시 문제가 생긴다. 
	class Logger : public Singleton<Logger>
	{
	private:
		Logger();
		~Logger();

	public:
		void Log(const char* str, ...);

	public:
		void Update();

	private:
		std::mutex m_log_mutex;
		std::list<std::string> m_logger_list;
		std::list<std::string> m_logger_outuput_list;

		#define MAX_LOG_BUFFER_SIZE 4096
		char m_log_buffer[MAX_LOG_BUFFER_SIZE];
	};
}

#define g_AYALogger Logger::GetInstance()