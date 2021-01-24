#include "pch.h"
#include "CppUnitTest.h"
#include "../AyaServerFramework/Util/Buffer/AyaBuffer.h"
#include "../AyaServerFramework/Util/Buffer/AyaBufferStream.h"
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
			AYA::BufferStream buffer_stream(&buffer);

			int input_value = 1144;

			buffer_stream.SetInt(input_value);

			int front_value = 0;

			bool front_int_result = buffer_stream.FrontInt(0, front_value);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, input_value:%d, front_value:%d", (int)front_int_result, input_value, front_value);

			Assert::AreEqual(input_value, front_value, logger_buffer);
		}

		TEST_METHOD(FrontIntNotChangeDataSize)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			int input_value = 1144;

			buffer_stream.SetInt(input_value);

			int front_value = 0;

			int before_front_buffer_data_size = (int)buffer.GetDataSize();

			buffer_stream.FrontInt(0, front_value);

			int after_front_buffer_data_size = (int)buffer.GetDataSize();

			Assert::AreEqual(before_front_buffer_data_size, after_front_buffer_data_size);
		}

		TEST_METHOD(SetIntIncreaseDataSize)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			int input_value = 1144;
			int integer_size = sizeof(int);

			bool set_int_result = buffer_stream.SetInt(input_value);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, input_size:%d, write_index:%d, buffer_size:%d", (int)set_int_result, integer_size, buffer.GetDataSize(), buffer.GetBufferSize());

			Assert::AreEqual(integer_size, (int)buffer.GetDataSize(), logger_buffer);
		}

		TEST_METHOD(GetIntIncreaseReadIndex)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			int input_value = 1144;
			int out_value = 0;

			buffer_stream.SetInt(input_value);

			unsigned int before_getint_read_cursor = buffer_stream.GetReadIndex();

			bool get_int_result = buffer_stream.GetInt(out_value);

			unsigned int after_getint_read_cursor = buffer_stream.GetReadIndex();

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, before:%d, after:%d", (int)get_int_result, before_getint_read_cursor, after_getint_read_cursor);

			Assert::IsTrue(after_getint_read_cursor > before_getint_read_cursor, logger_buffer);
		}

		TEST_METHOD(GetIntValidValue)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			int input_value = 1144;
			int output_value = 0;

			buffer_stream.SetInt(input_value);
			bool get_int_result = buffer_stream.GetInt(output_value);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, input:%d, output:%d", (int)get_int_result, input_value, output_value);
			Assert::AreEqual(input_value, output_value, logger_buffer);
		}

	};

	TEST_CLASS(ShortCase)
	{
		TEST_METHOD(SetShortIncreaseDataSize)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			short input_value = 72;
			int short_size = sizeof(short);

			bool set_short_result = buffer_stream.SetShort(input_value);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, input_size:%d, write_index:%d, buffer_size:%d", (int)set_short_result, short_size, buffer.GetDataSize(), buffer.GetBufferSize());

			Assert::AreEqual(short_size, (int)buffer.GetDataSize(), logger_buffer);
		}

		TEST_METHOD(GetShortIncreaseReadIndex)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			short input_value = 72;
			short out_value = 0;

			buffer_stream.SetShort(input_value);

			unsigned int before_getshort_read_index = buffer_stream.GetReadIndex();

			bool get_short_result = buffer_stream.GetShort(out_value);

			unsigned int after_geshort_read_index = buffer_stream.GetReadIndex();

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, before:%d, after:%d", (int)get_short_result, before_getshort_read_index, after_geshort_read_index);

			Assert::IsTrue(after_geshort_read_index > before_getshort_read_index, logger_buffer);
		}

		TEST_METHOD(GetShortValidValue)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			short input_value = 1144;
			short output_value = 0;

			buffer_stream.SetShort(input_value);
			bool get_short_result = buffer_stream.GetShort(output_value);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, input:%d, output:%d", (int)get_short_result, input_value, output_value);
			Assert::AreEqual(input_value, output_value, logger_buffer);
		}

	};

	TEST_CLASS(LongCase)
	{
		TEST_METHOD(SetLongIncreaseDataSize)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			long input_value = LONG_MAX;
			int long_size = sizeof(long);

			bool set_long_result = buffer_stream.SetLong(input_value);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, input_size:%d, write_index:%d, buffer_size:%d", (int)set_long_result, long_size, buffer.GetDataSize(), buffer.GetBufferSize());

			Assert::AreEqual(long_size, (int)buffer.GetDataSize(), logger_buffer);
		}

		TEST_METHOD(GetLongIncreaseReadIndex)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			long input_value = LONG_MAX;
			long out_value = 0;

			buffer_stream.SetLong(input_value);

			unsigned int before_getshort_read_index = buffer_stream.GetReadIndex();

			bool get_long_result = buffer_stream.GetLong(out_value);

			unsigned int after_geshort_read_index = buffer_stream.GetReadIndex();

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, before:%d, after:%d", (int)get_long_result, before_getshort_read_index, after_geshort_read_index);

			Assert::IsTrue(after_geshort_read_index > before_getshort_read_index, logger_buffer);
		}

		TEST_METHOD(GetLongValidValue)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			long input_value = LONG_MAX;
			long output_value = 0;

			buffer_stream.SetLong(input_value);
			bool get_long_result = buffer_stream.GetLong(output_value);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, input:%ld, output:%ld", (int)get_long_result, input_value, output_value);
			Assert::AreEqual(input_value, output_value, logger_buffer);
		}

	};

	TEST_CLASS(StringCase)
	{
		TEST_METHOD(SetStringIncreaseDataSize)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			std::wstring input_value = L"this is test wstring";
			int wstring_size = ((int)sizeof(wchar_t) * (int)input_value.length()) + (int)sizeof(short); // wstring의 length 변수와 wstring buffer의 사이즈를 합한게 wstring size 

			bool set_long_result = buffer_stream.SetString(input_value);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, input_size:%d, write_index:%d, buffer_size:%d", (int)set_long_result, wstring_size, (int)buffer.GetDataSize(), buffer.GetBufferSize());

			Assert::AreEqual(wstring_size, (int)buffer.GetDataSize(), logger_buffer);
		}

		TEST_METHOD(GetStringIncreaseReadIndex)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			std::wstring input_value = L"this is test wstring";
			std::wstring out_value;

			buffer_stream.SetString(input_value);

			unsigned int before_getshort_read_index = buffer_stream.GetReadIndex();

			bool get_string_result = buffer_stream.GetString(out_value);

			unsigned int after_geshort_read_index = buffer_stream.GetReadIndex();

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, before:%d, after:%d", (int)get_string_result, before_getshort_read_index, after_geshort_read_index);

			Assert::IsTrue(after_geshort_read_index > before_getshort_read_index, logger_buffer);
		}

		TEST_METHOD(GetStringValidValue)
		{
			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);

			std::wstring input_value = L"this is test wstring";
			std::wstring output_value;

			buffer_stream.SetString(input_value);
			bool get_long_result = buffer_stream.GetString(output_value);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, input:%ws, output:%ws", (int)get_long_result, input_value.c_str(), output_value.c_str());
			Assert::AreEqual(input_value, output_value, logger_buffer);
		}
	};

	class TestSubSerializableObject
	{
	public:
		int IntegerData;
		long LongData;

		friend AYA::BufferStream& operator<<(AYA::BufferStream& stream, TestSubSerializableObject& write)
		{
			stream << write.IntegerData;
			stream << write.LongData;

			return stream;
		}

		friend AYA::BufferStream& operator>>(AYA::BufferStream& stream, TestSubSerializableObject& read)
		{
			stream >> read.IntegerData;
			stream >> read.LongData;

			return stream;
		}

		bool TestSubSerializableObject::operator==(const TestSubSerializableObject& other) const
		{
			if (this->IntegerData != other.IntegerData)
			{
				return false;
			}

			if (this->LongData != other.LongData)
			{
				return false;
			}

			return true;
		}

		bool TestSubSerializableObject::operator!=(const TestSubSerializableObject& other) const
		{
			if (this->IntegerData == other.IntegerData)
			{
				return false;
			}

			if (this->LongData == other.LongData)
			{
				return false;
			}

			return true;
		}
	};

	class TestSerializableObject
	{
	public:
		int IntegerData;
		std::list<TestSubSerializableObject> SubObjectList;
		std::wstring WstringData;

		friend AYA::BufferStream& operator<<(AYA::BufferStream& stream, TestSerializableObject& write)
		{
			stream << write.IntegerData;

			{
				short list_size = (short)write.SubObjectList.size();
				stream << list_size;

				for (auto& sub_object : write.SubObjectList)
				{
					stream << sub_object;
				}
			}

			stream << write.WstringData;

			return stream;
		}

		friend AYA::BufferStream& operator>>(AYA::BufferStream& stream, TestSerializableObject& read)
		{
			stream >> read.IntegerData;

			{
				short list_size = 0;
				stream >> list_size;

				for (short i = 0; i < list_size; ++i)
				{
					TestSubSerializableObject sub_object;
					stream >> sub_object;
					read.SubObjectList.push_back(sub_object);
				}
			}

			stream >> read.WstringData;

			return stream;
		}

		bool TestSerializableObject::operator==(const TestSerializableObject& other) const
		{
			if (this->IntegerData != other.IntegerData)
			{
				return false;
			}

			if (this->WstringData != other.WstringData)
			{
				return false;
			}

			if (this->SubObjectList.size() != other.SubObjectList.size())
			{
				return false;
			}

			auto list_size = this->SubObjectList.size();
			auto this_list_iter = this->SubObjectList.begin();
			auto other_list_iter = other.SubObjectList.begin();

			for (size_t i = 0; i < list_size; ++i, ++this_list_iter, ++other_list_iter)
			{
				if ( (*this_list_iter) != (*other_list_iter))
				{
					return false;
				}
			}

			return true;
		}
	};

	TEST_CLASS(CustomCase)
	{
		TEST_METHOD(CustomSerilizeValid)
		{
			TestSerializableObject original_custom_object;
			original_custom_object.IntegerData = 44;
			original_custom_object.WstringData = L"TestWstringValue";

			for (int i = 1; i <= 4; ++i)
			{
				TestSubSerializableObject sub_object;
				sub_object.IntegerData = i;
				sub_object.LongData = (long)(i * 10000);
				original_custom_object.SubObjectList.push_back(sub_object);
			}

			AYA::Buffer buffer;
			AYA::BufferStream buffer_stream(&buffer);
			buffer_stream << original_custom_object;

			TestSerializableObject deserilize_custom_object;
			buffer_stream >> deserilize_custom_object;

			Assert::IsTrue(original_custom_object == deserilize_custom_object);
		}
	};

}