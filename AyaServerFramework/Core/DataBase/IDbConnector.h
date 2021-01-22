#pragma once

#include "./DBConnectData.h"

namespace AYA
{
	class IDBConnector
	{
	public:
		virtual bool Init() = 0;
		virtual bool Connect(const DBConnectData& db_connect_data) = 0;
		virtual void Release() = 0;
		virtual int GetLastError() = 0;
	};
}