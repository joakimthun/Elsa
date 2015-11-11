#include "struct_access_expression_builder.h"

#include "../../ast/struct_declaration_expression.h"

namespace elsa {
	namespace compiler {

		void StructAccessExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, StructAccessExpression* expression)
		{
			IdentifierExpressionBuilder::build(program, visitor, expression->get_base());

			for (const auto& field_exp : expression->get_expressions())
			{
				auto sde = expression->get_base()->get_type()->get_struct_declaration_expression();
				
				for (const auto& field : sde->get_fields())
				{
					if (field->get_name() == field_exp->get_name())
					{
						program->emit(OpCode::l_field);
						program->emit(static_cast<int>(field->get_index()));
						break;
					}
				}
			}
		}

	}
}
