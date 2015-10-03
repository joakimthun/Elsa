#pragma once

#include <memory>

#include "source_file.h"
#include "token.h"

namespace elsa {
	namespace compiler {

		class Lexer
		{
		public:
			Lexer(SourceFile* file);

			Token next_token();

		private:
			std::unique_ptr<SourceFile> file_;

		};

	}
}