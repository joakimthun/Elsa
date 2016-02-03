#include "identifier_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void IdentifierExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, IdentifierExpression* expression)
		{
			if (expression->get_type()->get_type() == ObjectType::Function && !expression->get_type()->get_func_declaration_expression()->anonymous())
			{
				auto function_info = program->get_func(expression->get_type()->get_func_declaration_expression()->get_name());
				program->emit(OpCode::fnconst);
				program->emit(static_cast<int>(function_info->get_addr()));
			}
			else
			{
				auto local = visitor->current_scope()->get_local(expression->get_name());

				auto load_inst = local->get_local_type() == LocalType::Local ? OpCode::l_local : OpCode::l_arg;

				program->emit(load_inst);
				program->emit(static_cast<int>(local->get_index()));
			}
		}

	}
}
