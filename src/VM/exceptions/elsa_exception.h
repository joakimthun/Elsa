#pragma once

#include <exception>
#include <string>

namespace elsa {
	namespace vm {

		class ElsaException : public std::exception
		{
		public:
			inline ElsaException(std::string message) : message_(message) {};

			virtual const char* what() const throw()
			{
				return message_.c_str();
			}

		protected:
			std::string message_;
		};

	}
}
