#include "pch.h"
#include "CppUnitTest.h"
#include "../AyaServerFramework/Util/Buffer/AyaBuffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBuffer
{
	TEST_CLASS(TestBufferClass)
	{
	public:

		TEST_METHOD(TestBufferResize)
		{

		}

		TEST_METHOD(TestBufferFrontIntValueValid)
		{
			AYA::Buffer buffer;

			int set_int_value = 1144;

			buffer.SetInt(set_int_value);

			int front_value = 0;

			buffer.FrontInt(0, front_value);

			Assert::AreEqual(set_int_value, front_value);
		}

		TEST_METHOD(TestBufferFrontIntNotChangeDataSize)
		{
			AYA::Buffer buffer;

			int test_value = 1144;

			buffer.SetInt(test_value);

			int front_value = 0;

			int before_front_buffer_data_size = buffer.GetBufferDataSize();

			buffer.FrontInt(0, front_value);

			int after_front_buffer_data_size = buffer.GetBufferDataSize();

			Assert::AreEqual(before_front_buffer_data_size, after_front_buffer_data_size);
		}
	};
}