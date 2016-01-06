#pragma once

#include <Windows.h>
#include <string>

namespace elsa {

	class StringUtil
	{
	public:
		static std::string utf8_encode(const std::wstring& wstr);
	};

	

}
