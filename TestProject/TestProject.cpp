#include "pch.h"
#include "CppUnitTest.h"
#include <WinSock2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	struct TestOverlappedData
	{
		OVERLAPPED OverlappedData;
	};

	class TestOverlappedClass
	{
	public:
		TestOverlappedData Data;
	};

	TEST_CLASS(TestProject)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			TestOverlappedClass test_class;

			ZeroMemory(&test_class, sizeof(test_class));

			test_class.Data.OverlappedData.Offset = 9999;
			
			DWORD test_value = 9999;

			TestOverlappedData* converted_overalpped_data = (TestOverlappedData*)(&test_class);

			Assert::AreEqual(test_value, converted_overalpped_data->OverlappedData.Offset);

		}
	};
}
