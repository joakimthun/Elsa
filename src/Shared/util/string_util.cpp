#include "string_util.h"

namespace elsa {

	std::string StringUtil::utf8_encode(const std::wstring & wstr)
	{
		if (wstr.empty())
			return std::string();

		auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
		std::string str_to(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str_to[0], size_needed, NULL, NULL);
		return str_to;
	}

}