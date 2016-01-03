#include "struct_access_expression_builder.h"

#include "../../ast/struct_declaration_expression.h"

namespace elsa {
	namespace compiler {

		void StructAccessExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, StructAccessExpression* expression)
		{
			IdentifierExpressionBuilder::build(program, visitor, expression->get_base());

			auto current_type = expression->get_base()->get_type()->get_struct_declaration_expression();
			for (const auto& exp : expression->get_expressions())
			{
				if (exp->get_expression_type() == ExpressionType::FieldAccess)
				{
					for (const auto& field : current_type->get_fields())
					{
						if (field->get_name() == exp->get_name())
						{
							if (field->get_type()->get_type() == ObjectType::GCOPtr)
								current_type = field->get_type()->get_struct_declaration_expression();

							program->emit(OpCode::l_field);
							program->emit(static_cast<int>(field->get_index()));
							break;
						}
					}
				}
				else if(exp->get_expression_type() == ExpressionType::FuncCall)
				{
					for (const auto& function : current_type->get_functions())
					{
						if (function->get_name() == exp->get_name())
						{
							const auto fi = program->get_struct(current_type->get_name())->get_function(function->get_name());

							if (function->get_return_type()->get_type() == ObjectType::GCOPtr)
								current_type = function->get_return_type()->get_struct_declaration_expression();

							FuncCallExpressionBuilder::build_member(program, visitor, dynamic_cast<FuncCallExpression*>(exp.get()), fi);
							break;
						}
					}
				}
			}
		}

	}
}
