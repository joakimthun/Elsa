#pragma once

#include <stdio.h>

#include "exceptions\elsa_exception.h"

namespace elsa {
	namespace compiler {

		class Token;

		class ParsingException : public ElsaException
		{
		public:
			ParsingException(const std::string& message);
			ParsingException(const std::wstring& message, Token* current_token);
			ParsingException(const std::wstring& message);

			virtual const char* what() const throw();

		private:
			std::wstring format_message(const std::wstring& message, Token* current_token);
		};
	}
}
