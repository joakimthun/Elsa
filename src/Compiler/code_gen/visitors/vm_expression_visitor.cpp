#include "vm_expression_visitor.h"

#include "../../ast/func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		VMExpressionVisitor::VMExpressionVisitor()
			:
			vm_program_(std::make_unique<VMProgram>())
		{}

		void VMExpressionVisitor::visit(FuncDeclarationExpression* expression)
		{
			
		}

	}
}