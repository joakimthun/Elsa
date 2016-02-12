#pragma once

#include <memory>

#include "lexing\source_file.h"
#include "lexing\lexer.h"
#include "parsing\elsa_parser.h"
#include "code_gen\code_gen.h"
#include "util\string_util.h"
#include "ast_rewrite/ast_rewriters.h"

namespace elsa {
	namespace compiler {

		class Compiler
		{
		public:
			static std::unique_ptr<VMProgram> compile(const wchar_t* filename);
			static std::unique_ptr<VMProgram> compile(const char* filename);
		private:
			static std::unique_ptr<VMProgram> compile_impl(const wchar_t* filename);
		};

	}
}
