#pragma once

#include "exceptions\elsa_exception.h"

namespace elsa {
	namespace compiler {

		class ParsingException : public ElsaException
		{
		public:
			ParsingException(const std::string& message);
			ParsingException(const std::wstring& message);

			virtual const char* what() const throw();
		};
	}
}
