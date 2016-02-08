#include "struct_access_expression_builder.h"

#include "../../ast/struct_declaration_expression.h"
#include "../../ast/array_access_expression.h"
#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void StructAccessExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, StructAccessExpression* expression, const ElsaType* current)
		{
			// If we do not have a base expression we can expect the base to already be on the stack e.g. chained array access.
			if(expression->get_base() != nullptr)
				IdentifierExpressionBuilder::build(program, visitor, expression->get_base());

			auto current_type = current;
			if (current_type == nullptr)
			{
				current_type = visitor->current_type();

				if (expression->get_base() != nullptr)
					current_type = expression->get_base()->get_type();
			}

			for (const auto& exp : expression->get_expressions())
			{
				auto current_struct = get_current_struct(current_type);

				if (exp->get_expression_type() == ExpressionType::FieldAccess)
				{
					for (const auto& field : current_struct->get_fields())
					{
						if (field->get_name() == exp->get_name())
						{
							if (field->get_type()->get_type() == ObjectType::GCOPtr)
								current_type = field->get_type();

							program->emit(OpCode::l_field);
							program->emit(static_cast<int>(field->get_index()));
							break;
						}
					}
				}
				else if(exp->get_expression_type() == ExpressionType::FuncCall)
				{
					for (const auto& function : current_struct->get_functions())
					{
						if (function->get_name() == exp->get_name())
						{
							const auto fi = program->get_struct(current_type->get_struct_declaration_expression()->get_name(true))->get_function(function->get_name());

							if (function->get_return_type()->get_type() == ObjectType::GCOPtr)
								current_type = function->get_return_type();

							FuncCallExpressionBuilder::build_member(program, visitor, dynamic_cast<FuncCallExpression*>(exp.get()), fi);
							break;
						}
					}
				}
				else if (exp->get_expression_type() == ExpressionType::ArrayAccess)
				{
					for (const auto& field : current_struct->get_fields())
					{
						if (field->get_name() == exp->get_name())
						{
							current_type = field->get_type()->get_struct_declaration_expression()->get_generic_type();

							program->emit(OpCode::l_field);
							program->emit(static_cast<int>(field->get_index()));

							dynamic_cast<ArrayAccessExpression*>(exp.get())->get_index_expression()->accept(visitor);
							program->emit(OpCode::l_ele);
							break;
						}
					}
				}
				else if (exp->get_expression_type() == ExpressionType::Identifier)
				{
					if (exp->get_type()->get_type() == ObjectType::Function)
					{
						for (const auto& function : current_struct->get_functions())
						{
							if (function->get_name() == exp->get_name())
							{
								const auto fi = program->get_struct(current_type->get_struct_declaration_expression()->get_name(true))->get_function(function->get_name());
								program->emit(OpCode::fnconst);
								program->emit(static_cast<int>(fi->get_addr()));
								break;
							}
						}
					}
					else
					{
						throw CodeGenException("Unsupported type -> StructAccessExpressionBuilder -> ExpressionType::Identifier");
					}
				}
			}
		}

		const StructDeclarationExpression* StructAccessExpressionBuilder::get_current_struct(const ElsaType* current_type)
		{
			if (current_type->get_type() == ObjectType::GCOPtr)
				return current_type->get_struct_declaration_expression();

			if (current_type->get_type() == ObjectType::Function)
				return current_type->get_func_declaration_expression()->get_return_type()->get_struct_declaration_expression();

			return nullptr;
		}

	}
}
