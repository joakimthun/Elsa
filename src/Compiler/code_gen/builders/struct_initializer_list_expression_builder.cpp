#include "struct_initializer_list_expression_builder.h"

#include "../vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void StructInitializerListExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, StructInitializerListExpression* expression)
		{
			auto si = program->get_struct(expression->get_create_struct_expression()->get_struct_name());

			if (si == nullptr)
				throw CodeGenException("No struct with that name has been defined");

			program->emit(OpCode::new_struct);
			program->emit(static_cast<int>(si->get_index()));

			auto local_index = visitor->current_scope()->create_new_local();

			program->emit(OpCode::s_local);
			program->emit(static_cast<int>(local_index));

			for (auto& exp : expression->get_value_expressions())
			{
				program->emit(OpCode::l_local);
				program->emit(static_cast<int>(local_index));
				exp->get_value()->accept(visitor);

				program->emit(OpCode::s_field);
				program->emit(static_cast<int>(exp->get_index()));
			}

			program->emit(OpCode::l_local);
			program->emit(static_cast<int>(local_index));
		}
	}
}
