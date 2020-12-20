#pragma once

#include "./OverlappedData.h"
#include <memory>
#include <queue>
#include "../../Util/Singleton/Singleton.h"

#include <mutex>

namespace AYA
{
	typedef std::shared_ptr<OverlappedData> OverlappedDataPointer;
	typedef std::queue< OverlappedDataPointer > OverlappedDataPool;

	class OveralppedIOManager : public Singleton<OveralppedIOManager>
	{
	public:
		OveralppedIOManager();
		~OveralppedIOManager();

		
	private:
		void Reserve(int reserve_pool_size);
		const int OVERLAPPED_POOL_RESERVE_SIZE = 300;
	public:
		OverlappedDataPointer PopOverlappedData(OVERLAPPED_IO_TYPE io_type);
		void PushOverlappedData(OverlappedDataPointer overlapped_data);
	
	private:
		OverlappedDataPool m_overlapped_data_pool;
		std::mutex m_overalpped_lock;
	};

	#define g_OverlappedIOManager OveralppedIOManager::GetInstance()

}