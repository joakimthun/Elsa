#pragma once


#include "../../ast/func_declaration_expression.h"
#include "constants\function_info.h"

namespace elsa {
	namespace compiler {

		class FunctionBuilder
		{
		public:
			static FunctionInfo* build(FuncDeclarationExpression* expression);
		};

	}
}