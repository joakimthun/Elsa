#pragma once

#include <memory>
#include <string>
#include <cstddef>

#include "exceptions\codegen_exception.h"
#include "../../ast/elsa_invoke_expression.h"
#include "opcodes\opcodes.h"
#include "vm_program.h"

namespace elsa {
	namespace compiler {

		class VMExpressionVisitor;

		class ElsaInvokeExpressionBuilder
		{
		public:
			static void build(VMProgram* program, VMExpressionVisitor* visitor, ElsaInvokeExpression* expression);
		};

	}
}