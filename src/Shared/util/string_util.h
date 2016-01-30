#pragma once

#include <Windows.h>
#include <string>
#include <stdlib.h>

namespace elsa {

	class StringUtil
	{
	public:
		static std::string utf8_encode(const std::wstring& wstr);
		static std::wstring to_wchar(const char* str);
		static std::wstring create_random_string(std::size_t length);
	};

	

}
