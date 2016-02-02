#include "func_call_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void FuncCallExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, FuncCallExpression* expression)
		{
			if(expression->stack_invoke())
				build_stack_invoke(program, visitor, expression);
			else
				build(program, visitor, expression, program->get_func(expression->get_name()));
		}

		void FuncCallExpressionBuilder::build_member(VMProgram* program, VMExpressionVisitor* visitor, FuncCallExpression* expression, const FunctionInfo* fi)
		{
			build(program, visitor, expression, fi);
		}

		void FuncCallExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, FuncCallExpression* expression, const FunctionInfo* fi)
		{
			for (auto& arg : expression->get_args())
			{
				arg->accept(visitor);
			}

			program->emit(OpCode::call);
			program->emit(static_cast<int>(fi->get_addr()));
		}

		void FuncCallExpressionBuilder::build_stack_invoke(VMProgram* program, VMExpressionVisitor* visitor, FuncCallExpression* expression)
		{
			for (auto& arg : expression->get_args())
			{
				arg->accept(visitor);
			}

			auto local = visitor->current_scope()->get_local(expression->local_name());
			auto load_inst = local->get_local_type() == LocalType::Local ? OpCode::l_local : OpCode::l_arg;

			program->emit(load_inst);
			program->emit(static_cast<int>(local->get_index()));
			program->emit(OpCode::scall);
		}
	}
}
