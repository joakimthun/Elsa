#include "elsa_invoke_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ElsaInvokeExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, ElsaInvokeExpression* expression)
		{
			const auto& native_function_info = visitor->native_function_table().get(expression->get_function_name());

			std::size_t index = 0;
			for (auto& arg : expression->get_args())
			{
				arg->accept(visitor);

				index++;
			}

			program->emit(OpCode::elsa);
			program->emit(static_cast<int>(native_function_info->get_index()));

		}

	}
}

