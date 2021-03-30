#pragma once

namespace AYA
{
	struct SocketOption
	{
		const char* IP = nullptr;
		short Port = 0;
		bool Is_Listen = false;
	};
}
