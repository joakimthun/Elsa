#include "elsa_exception.h"

#include "../util/string_util.h"

namespace elsa {

	ElsaException::ElsaException(const std::string& message) : message_(message) {};
	
	ElsaException::ElsaException(const std::wstring& message)
	{
		message_ = StringUtil::utf8_encode(message);
	};
	
	const char* ElsaException::what() const throw()
	{
		return message_.c_str();
	}

}