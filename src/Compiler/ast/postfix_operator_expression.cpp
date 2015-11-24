#include "postfix_operator_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		void PostfixOperatorExpression::set_operator(TokenType op)
		{
			operator_ = op;
		}

		void PostfixOperatorExpression::set_expression(std::unique_ptr<Expression> expression)
		{
			expression_ = std::move(expression);
		}

		void PostfixOperatorExpression::set_type(ElsaType* type)
		{
			type_ = std::unique_ptr<ElsaType>(type);
		}

		TokenType PostfixOperatorExpression::get_operator() const
		{
			return operator_;
		}
		
		Expression* PostfixOperatorExpression::get_expression() const
		{
			return expression_.get();
		}

		ElsaType* PostfixOperatorExpression::get_type() const
		{
			return type_.get();
		}

		void PostfixOperatorExpression::accept(ExpressionVisitor* visitor)
		{

		}
		
	}
}
