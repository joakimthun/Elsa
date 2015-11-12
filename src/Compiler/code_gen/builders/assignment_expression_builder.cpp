#include "assignment_expression_builder.h"

#include "../../ast/struct_declaration_expression.h"
#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void AssignmentExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, AssignmentExpression* expression)
		{
			if (auto sae = dynamic_cast<StructAccessExpression*>(expression->get_left()))
			{
				IdentifierExpressionBuilder::build(program, visitor, sae->get_base());

				for (auto it = sae->get_expressions().begin(); it != sae->get_expressions().end(); ++it)
				{
					auto sde = sae->get_base()->get_type()->get_struct_declaration_expression();

					for (const auto& field : sde->get_fields())
					{
						if (field->get_name() == it->get()->get_name())
						{
							// Last element, we store the value in this field
							if (std::next(it) == sae->get_expressions().end())
							{
								expression->get_right()->accept(visitor);
								program->emit(OpCode::s_field);
								program->emit(static_cast<int>(field->get_index()));
							}
							else
							{
								program->emit(OpCode::l_field);
								program->emit(static_cast<int>(field->get_index()));
							}
							
							break;
						}
					}
				}

				return;
			}

			throw CodeGenException("Not supported -> AssignmentExpressionBuilder");
		}

	}
}
