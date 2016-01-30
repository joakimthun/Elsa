#pragma once

#include <memory>
#include <utility>

#include "exceptions\codegen_exception.h"
#include "../../ast/func_declaration_expression.h"
#include "constants\function_info.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class FunctionDeclarationExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, FuncDeclarationExpression* expression);
			static const FunctionInfo* build_member(VMProgram* program, VMExpressionVisitor* visitor, FuncDeclarationExpression* expression);

		private:
			static const FunctionInfo* build_internal(VMProgram* program, VMExpressionVisitor* visitor, FuncDeclarationExpression* expression);
		};

	}
}