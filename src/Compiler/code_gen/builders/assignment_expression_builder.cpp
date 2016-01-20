#include "assignment_expression_builder.h"

#include "../../ast/struct_declaration_expression.h"
#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void AssignmentExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, AssignmentExpression* expression)
		{
			if (auto sae = dynamic_cast<StructAccessExpression*>(expression->get_left()))
			{
				auto field_index = LoadHelper::load_field(program, visitor, sae);
				expression->get_right()->accept(visitor);

				program->emit(OpCode::s_field);
				program->emit(static_cast<int>(field_index));

				// TODO: Refactor this
				if (auto aie = dynamic_cast<ArrayInitializerListExpression*>(expression->get_right()))
				{
					for (const auto& exp : aie->get_values())
					{
						LoadHelper::load_field(program, visitor, sae, true);
						exp->accept(visitor);
						program->emit(OpCode::a_ele);
					}
				}

				return;
			}
			else if (auto ie = dynamic_cast<IdentifierExpression*>(expression->get_left()))
			{
				auto local_index = LoadHelper::load_local(program, visitor, ie);
				expression->get_right()->accept(visitor);

				program->emit(OpCode::s_local);
				program->emit(static_cast<int>(local_index));

				build_initializer_list(expression->get_right(), local_index, program, visitor, l_local);

				return;
			}
			else if (auto aae = dynamic_cast<ArrayAccessExpression*>(expression->get_left()))
			{
				auto local_index = LoadHelper::load_local(program, visitor, aae->get_identifier_expression());
				expression->get_right()->accept(visitor);
				aae->get_index_expression()->accept(visitor);
				program->emit(OpCode::s_ele);

				return;
			}

			throw CodeGenException("Not supported -> AssignmentExpressionBuilder");
		}

		void AssignmentExpressionBuilder::build_initializer_list(Expression* exp, std::size_t index, VMProgram* program, VMExpressionVisitor* visitor, OpCode load_inst)
		{
			if (auto aie = dynamic_cast<ArrayInitializerListExpression*>(exp))
			{
				for (const auto& exp : aie->get_values())
				{
					program->emit(load_inst);
					program->emit(static_cast<int>(index));
					exp->accept(visitor);
					program->emit(OpCode::a_ele);
				}
			}
		}

		bool AssignmentExpressionBuilder::is_initializer_list(Expression* exp)
		{
			return dynamic_cast<ArrayInitializerListExpression*>(exp) != nullptr;
		}

	}
}
