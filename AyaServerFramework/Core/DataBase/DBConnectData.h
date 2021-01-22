#pragma once

#include <string>

namespace AYA
{
	struct DBConnectData
	{
		std::string Host;
		std::string User;
		std::string Password;
		std::string Database;
		short Port;
	};
}