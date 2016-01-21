#include "variable_builder.h"
#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void VariableBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, VariableDeclarationExpression* expression)
		{
			expression->get_expression()->accept(visitor);

			program->emit(OpCode::s_local);

			auto local = visitor->current_scope()->get_local(expression->get_name());

			auto local_index = local->get_index();
			program->emit(static_cast<int>(local_index));

			if (auto aie = dynamic_cast<ArrayInitializerListExpression*>(expression->get_expression()))
			{
				for(const auto& exp : aie->get_values())
				{
					program->emit(l_local);
					program->emit(static_cast<int>(local_index));
					exp->accept(visitor);
					program->emit(OpCode::a_ele);
				}
			}
			else if (auto sle = dynamic_cast<StringLiteralExpression*>(expression->get_expression()))
			{
				program->emit(l_local);
				program->emit(static_cast<int>(local_index));

				program->emit(OpCode::iconst);
				program->emit(sle->get_value().size());
				program->emit(OpCode::new_arr);
				program->emit(static_cast<int>(VMType::Char));

				program->emit(OpCode::s_field);
				program->emit(0);

				for (auto c : sle->get_value())
				{
					program->emit(l_local);
					program->emit(static_cast<int>(local_index));
					program->emit(OpCode::l_field);
					program->emit(0);
					program->emit(OpCode::cconst);
					auto char_index = program->add_char(std::make_unique<CharInfo>(c));
					program->emit(static_cast<int>(char_index));
					program->emit(OpCode::a_ele);
				}
			}
		}

	}
}
