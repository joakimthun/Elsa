#pragma once

#include <exception>
#include <string>

namespace elsa {

		class ElsaException : public std::exception
		{
		public:
			ElsaException(const std::string& message);
			ElsaException(const std::wstring& message);

			virtual const char* what() const throw();

		protected:
			std::string message_;
		};

}
