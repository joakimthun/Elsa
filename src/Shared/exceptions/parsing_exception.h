#pragma once

#include "elsa_exception.h"

namespace elsa {

	class ParsingException : public ElsaException
	{
	public:
		ParsingException(const std::string& message) : ElsaException(message) {};
		ParsingException(const std::wstring& message) : ElsaException(message) {};

		virtual const char* what() const throw()
		{
			return message_.c_str();
		}
	};

}
