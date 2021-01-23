#include "pch.h"
#include "CppUnitTest.h"
#include <mysql.h>
#include <atlstr.h> 
#include "../AyaServerFramework/Util/Base64/Base64.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBase64
{
	// Âü°í : https://www.base64encode.org/
	const std::string valid_encoded_str = "cGFzc3dvcmQxMjQh";
	const std::string valid_decoded_str = "password124!";

	const std::wstring valid_encoded_wstr = L"cGFzc3dvcmQxMjQh";
	const std::wstring valid_decoded_wstr = L"password124!";

	TEST_CLASS(EncodeBasicCase)
	{
	public:
		TEST_METHOD(EncodeValid)
		{
			std::string encoded_str;

			Util::Base64::Encode(valid_decoded_str, encoded_str);

			bool test_result = valid_encoded_str == encoded_str;

			std::wstring encoded_wstr = CA2W(encoded_str.c_str());

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"encode_result:%d, valid_str:%s, result_str:%s", (int)test_result, valid_encoded_wstr.c_str(), encoded_wstr.c_str());
			Assert::IsTrue(test_result, logger_buffer);
		}
	};

	TEST_CLASS(DecodeBasicCase)
	{
	public:
		TEST_METHOD(DecodeValid)
		{
			std::string decoded_str;

			bool decode_result = Util::Base64::Decode(valid_encoded_str, decoded_str);
			
			bool test_result = decoded_str == valid_decoded_str;

			std::wstring decoded_wstr = CA2W(decoded_str.c_str());

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"decode_result:%d, valid_str:%s, result_str:%s", (int)test_result, valid_decoded_wstr.c_str(), decoded_wstr.c_str());
			Assert::IsTrue(test_result, logger_buffer);
		}
	};
}