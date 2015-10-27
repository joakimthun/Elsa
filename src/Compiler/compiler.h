#pragma once

#include <memory>

#include "lexing\source_file.h"
#include "lexing\lexer.h"
#include "parsing\elsa_parser.h"
#include "code_gen\code_gen.h"

namespace elsa {
	namespace compiler {

		class Compiler
		{
		public:
			static VMProgram* compile(const char* filename);
		private:
		};

	}
}
