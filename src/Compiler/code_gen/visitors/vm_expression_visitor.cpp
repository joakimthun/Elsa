#include "vm_expression_visitor.h"

#include "../../ast/func_declaration_expression.h"
#include "../../ast/variable_declaration_expression.h"
#include "../../ast/binary_operator_expression.h"
#include "../../ast/integer_literal_expression.h"

namespace elsa {
	namespace compiler {

		VMExpressionVisitor::VMExpressionVisitor()
			:
			vm_program_(std::make_unique<VMProgram>())
		{}

		void VMExpressionVisitor::visit(FuncDeclarationExpression* expression)
		{
			FunctionBuilder::build(vm_program_.get(), this, expression);
		}

		void VMExpressionVisitor::visit(VariableDeclarationExpression* expression)
		{

		}

		void VMExpressionVisitor::visit(BinaryOperatorExpression* expression)
		{

		}

		void VMExpressionVisitor::visit(IntegerLiteralExpression* expression)
		{

		}

	}
}