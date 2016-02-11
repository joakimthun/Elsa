#pragma once

#include <memory>

#include "../ast/struct_declaration_expression.h"

namespace elsa {
	namespace compiler {

		class ElsaParser;
		class Program;

		class StructFactory
		{
		public:
			static std::unique_ptr<StructDeclarationExpression> create(ElsaParser* parser);
		};

	}
}
