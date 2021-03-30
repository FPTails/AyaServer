#include "stdafx.h"
#include "Logger.h"




namespace AYA
{
	Logger::Logger()
	{

	}

	Logger::~Logger()
	{

	}

	void Logger::Log(const char* str, ...)
	{
		std::lock_guard<std::mutex> logger_list_lock(m_log_mutex);

		va_list args;
		
		va_start(args, str);
		vsprintf_s(m_log_buffer, MAX_LOG_BUFFER_SIZE, str, args);
		va_end(args);

		m_log_buffer[MAX_LOG_BUFFER_SIZE - 1] = '\0';
		std::string new_log_string = m_log_buffer;
		
		m_logger_list.emplace_back(new_log_string);
	}


	void Logger::Update()
	{
		{
			std::lock_guard<std::mutex> logger_list_lock(m_log_mutex);
			std::swap(m_logger_list, m_logger_outuput_list); // 출력용 리스트와 교체해준다.
		}

		if (m_logger_outuput_list.empty())
		{
			return;
		}

		for (auto& curr_log : m_logger_outuput_list)
		{
			printf("%s\n", curr_log.c_str());
		}

		m_logger_outuput_list.clear();
	}
}