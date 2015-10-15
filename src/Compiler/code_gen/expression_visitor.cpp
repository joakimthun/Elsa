#include "expression_visitor.h"

#include "../ast/func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		ExpressionVisitor::ExpressionVisitor()
		{}

		void ExpressionVisitor::visit(FuncDeclarationExpression* expression) 
		{
			auto name = expression->get_name();
		}

	}
}