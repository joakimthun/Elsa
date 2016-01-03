#include "func_call_expression_builder.h"

#include "../visitors/vm_expression_visitor.h"

namespace elsa {
	namespace compiler {

		void FuncCallExpressionBuilder::build(VMProgram* program, VMExpressionVisitor* visitor, FuncCallExpression* expression)
		{
			auto fi = program->get_func(expression->get_name());
			build(program, visitor, expression, fi);
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
	}
}
