#include "elsa_invoke_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ElsaInvokeExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, ElsaInvokeExpression* expression)
		{
			for (auto& arg : expression->get_args())
			{
				arg->accept(visitor);
			}

			program->emit(get_opcode(expression->get_function_name()));
		}

		OpCode ElsaInvokeExpressionBuilder::get_opcode(const std::wstring& function_name)
		{
			if (function_name == L"PrintLn")
			{
				return OpCode::print_ln;
			}

			throw CodeGenException("Unsupported native function name");
		}

	}
}

