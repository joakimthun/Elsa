#pragma once

#include <sstream>
#include <fstream>
#include <codecvt>
#include <cstddef>

#include "exceptions\elsa_exception.h"

namespace elsa {
	namespace compiler {

		class SourceFile
		{
		public:
			SourceFile(const char* filename);

			wchar_t next_char();

		private:
			void read_file(const char* filename);

			std::wstringstream stream_;
		};

	}
}
