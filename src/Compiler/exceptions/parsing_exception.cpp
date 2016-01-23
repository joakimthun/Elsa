#include "parsing_exception.h"

#include "..\token.h"

namespace elsa {
	namespace compiler {

		ParsingException::ParsingException(const std::string & message) : ElsaException(message) {};

		ParsingException::ParsingException(const std::wstring& message, Token* current_token) : ElsaException(format_message(message, current_token)) {}

		ParsingException::ParsingException(const std::wstring & message) : ElsaException(message) {};

		const char* ParsingException::what() const throw()
		{
			return message_.c_str();
		}

		std::wstring ParsingException::format_message(const std::wstring& message, Token* current_token)
		{
			wchar_t buf[1024];
			int len = swprintf_s(buf, 1024, L"%s \r\nat line: %d in %s", message.c_str(), current_token->get_line_number(), current_token->get_file_name().c_str());

			return std::wstring(buf, len);
		}
	}
}
