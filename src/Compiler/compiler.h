#pragma once

#include "lexing\source_file.h"
#include "lexing\lexer.h"
#include "parsing\elsa_parser.h"

namespace elsa {
	namespace compiler {

		class Compiler
		{
		public:
			static void compile(const char* filename);
		private:
		};

	}
}
