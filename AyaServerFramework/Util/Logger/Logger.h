#pragma once

#include "../Singleton/Singleton.h"
#include <mutex>
#include <list>

namespace AYA
{
	// Logger Class�� ���� �ֱ⸶�� Update�� ȣ������� �Ѵ�. 
	// �ֱ�� ������� ��ȣ�� ���� �������� , �������� �ִ�.
	// ��, Update�� �ϳ��� �����忡���� ȣ���ؾ� �Ѵ�. ���������尡 ȣ���ҽ� ������ �����. 
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