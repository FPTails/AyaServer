#include "stdafx.h"
#include "OverlappedIOManager.h"

namespace AYA
{
	OveralppedIOManager::OveralppedIOManager()
	{
		Reserve(OVERLAPPED_POOL_RESERVE_SIZE);
	}

	OveralppedIOManager::~OveralppedIOManager()
	{

	}

	void OveralppedIOManager::Reserve(int reserve_pool_size)
	{
		if (false == m_overlapped_data_pool.empty())
		{
			OverlappedDataPool empty_queue;
			std::swap(m_overlapped_data_pool, empty_queue);
		}

		for (int i = 0; i < reserve_pool_size; ++i)
		{
			auto new_overalpped_data = std::make_shared<OverlappedData>();

			ZeroMemory(&new_overalpped_data->WSAOverlapped, sizeof(new_overalpped_data->WSAOverlapped));
			ZeroMemory(&new_overalpped_data->WSABuffer, sizeof(new_overalpped_data->WSABuffer));
			new_overalpped_data->WSABuffer;
			new_overalpped_data->IOType = OVERLAPPED_IO_TYPE::NONE;
			new_overalpped_data->SessionObject = nullptr;

			m_overlapped_data_pool.push(new_overalpped_data);
		}
	}

	OverlappedDataPointer OveralppedIOManager::PopOverlappedData(OVERLAPPED_IO_TYPE io_type)
	{
		std::lock_guard<std::mutex> lock(m_overalpped_lock);

		if (m_overlapped_data_pool.empty())
		{
			Reserve(OVERLAPPED_POOL_RESERVE_SIZE);
		}

		auto front_data = m_overlapped_data_pool.front();
		front_data->IOType = io_type;
		m_overlapped_data_pool.pop();

		return front_data;
	}

	void OveralppedIOManager::PushOverlappedData(OverlappedDataPointer overlapped_data)
	{
		std::lock_guard<std::mutex> lock(m_overalpped_lock);

		overlapped_data->IOType = OVERLAPPED_IO_TYPE::NONE;
		overlapped_data->SessionObject = nullptr;

		m_overlapped_data_pool.push(overlapped_data);
	}
}