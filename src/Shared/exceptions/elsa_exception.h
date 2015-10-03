#pragma once

#include <exception>
#include <string>

namespace elsa {

		class ElsaException : public std::exception
		{
		public:
			ElsaException(const std::string& message) : message_(message) {};

			virtual const char* what() const throw()
			{
				return message_.c_str();
			}

		protected:
			std::string message_;
		};

}