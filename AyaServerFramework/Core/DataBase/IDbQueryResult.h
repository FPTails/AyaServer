#pragma once

#include "./IDbRow.h"

namespace AYA
{
	class IDBQueryResult
	{
	public:
		virtual IDBRow* Next() = 0;
	};
}
