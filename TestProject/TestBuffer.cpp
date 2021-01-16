#include "pch.h"
#include "CppUnitTest.h"
#include "../AyaServerFramework/Util/Buffer/AyaBuffer.h"
#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBuffer
{
	TEST_CLASS(IntegerCase)
	{
	public:
		TEST_METHOD(FrontIntValueValid)
		{
			AYA::Buffer buffer;

			int set_int_value = 1144;

			buffer.SetInt(set_int_value);

			int front_value = 0;

			buffer.FrontInt(0, front_value);

			Assert::AreEqual(set_int_value, front_value);
		}

		TEST_METHOD(FrontIntNotChangeDataSize)
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

		TEST_METHOD(SetIntIncreaseDataSize)
		{
			AYA::Buffer buffer;

			int test_value = 1144;
			int integer_size = sizeof(int);

			buffer.SetInt(test_value);

			Assert::AreEqual(integer_size, buffer.GetBufferDataSize());
		}

		TEST_METHOD(GetIntReduceReadCursor)
		{
			AYA::Buffer buffer;

			int test_value = 1144;
			int out_value = 0;

			buffer.SetInt(test_value);

			int before_getint_read_cursor = buffer.GetReadCursor();

			bool get_int_has_success = buffer.GetInt(out_value);

			int after_getint_read_cursor = buffer.GetReadCursor();

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, before:%d, after:%d", (int)get_int_has_success, before_getint_read_cursor, after_getint_read_cursor);

			Assert::IsTrue(after_getint_read_cursor > before_getint_read_cursor, logger_buffer);
		}

		TEST_METHOD(GetIntValidValue)
		{
			AYA::Buffer buffer;

			int input_value = 1144;
			int output_value = 0;

			buffer.SetInt(input_value);
			bool get_int_has_success = buffer.GetInt(output_value);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, input:%d, output:%d", (int)get_int_has_success, input_value, output_value);
			Assert::AreEqual(input_value, output_value, logger_buffer);
		}

	};

	TEST_CLASS(LongCase)
	{

	};

	TEST_CLASS(StringCase)
	{

	};
}