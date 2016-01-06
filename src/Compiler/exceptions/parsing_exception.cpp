#include "parsing_exception.h"

namespace elsa {
	namespace compiler {

			ParsingException::ParsingException(const std::string& message) : ElsaException(message) {};
			ParsingException::ParsingException(const std::wstring& message) : ElsaException(message) {};

			const char* ParsingException::what() const throw()
			{
				return message_.c_str();
			}
	}
}
