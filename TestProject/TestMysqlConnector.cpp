#include "pch.h"
#include "CppUnitTest.h"
#include <mysql.h>
#include <atlstr.h> 
#include "../AyaServerFramework/Core/DataBase/DBConnectData.h"
#include "../AyaServerFramework/Core/DataBase/Mysql/MysqlConnector.h"
#include "TestDataBaseEssential.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDataBase
{
	TEST_CLASS(MysqlConnectorBasicCase)
	{
	public:
		
		TEST_METHOD(InitValid)
		{
			AYA::MysqlConnector connector;

			bool init_result =  connector.Init();

			Assert::IsTrue(init_result);

			connector.Release();
		}

		TEST_METHOD(ConnectValid)
		{
			AYA::MysqlConnector connector;

			bool init_result = connector.Init();

			bool connect_result = connector.Connect(valid_connect_data);

			Assert::IsTrue(connect_result);

			connector.Release();
		}
	};

}