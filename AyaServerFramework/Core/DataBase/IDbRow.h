#pragma once

namespace AYA
{
	class IDBRow
	{
	public:
		virtual char* Get(unsigned short index) = 0;
		virtual void Set(char** data) = 0;
	};
}