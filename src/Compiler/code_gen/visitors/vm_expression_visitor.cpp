#include "vm_expression_visitor.h"

#include "../../ast/func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		VMExpressionVisitor::VMExpressionVisitor()
		{}

		void VMExpressionVisitor::visit(FuncDeclarationExpression* expression)
		{
			std::wcout << expression->get_name() << std::endl;
			std::wcout << expression->get_return_type()->get_type() << std::endl;
		}

	}
}