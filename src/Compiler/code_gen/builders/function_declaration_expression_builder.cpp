#include "function_declaration_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void FunctionDeclarationExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, FuncDeclarationExpression* expression)
		{
			auto fi = std::make_unique<FunctionInfo>(expression->get_name());
			fi->set_num_args(expression->get_num_args());
			fi->set_num_locals(expression->get_num_locals());

			if (expression->get_name() == L"main")
			{
				if (program->get_entry_point() != -1)
					throw CodeGenException("An entry point has alredy been defined");

				program->set_entry_point(static_cast<int>(program->get_next_instruction_index()));
			}

			fi->set_addr(static_cast<int>(program->get_next_instruction_index()));

			visitor->set_current_scope(expression);

			for (auto& exp : expression->get_body())
			{
				exp->accept(visitor);
			}

			program->add_func(std::move(fi));

			visitor->reset_current_scope();
		}

	}
}