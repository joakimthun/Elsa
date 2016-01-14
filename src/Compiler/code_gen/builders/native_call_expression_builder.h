#pragma once

#include <memory>
#include <string>
#include <cstddef>

#include "exceptions\codegen_exception.h"
#include "../../ast/func_call_expression.h"
#include "opcodes\opcodes.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class NativeCallExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, FuncCallExpression* expression);
		};

	}
}