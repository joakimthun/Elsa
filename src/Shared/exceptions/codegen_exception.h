#pragma once

#include "elsa_exception.h"

namespace elsa {

	class CodeGenException : public ElsaException
	{
	public:
		CodeGenException(const std::string& message) : ElsaException(message) {};

		virtual const char* what() const throw()
		{
			return message_.c_str();
		}
	};

}
