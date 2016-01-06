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
			SourceFile(const wchar_t* filename);

			wchar_t next_char();
			wchar_t peek_char();
			bool good() const;
			const std::wstring& get_file_name() const;

		private:
			void read_file(const wchar_t* filename);

			std::wstringstream stream_;
			std::wstring file_name_;
		};

	}
}
