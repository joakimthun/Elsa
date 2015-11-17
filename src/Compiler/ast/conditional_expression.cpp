#include "conditional_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {

		void ConditionalExpression::set_condition(std::unique_ptr<Expression> expression)
		{
			condition_ = std::move(expression);
		}

		void ConditionalExpression::add_to_if_body(std::unique_ptr<Expression> expression)
		{
			if_body_.push_back(std::move(expression));
		}

		void ConditionalExpression::add_to_else_body(std::unique_ptr<Expression> expression)
		{
			else_body_.push_back(std::move(expression));
		}

		Expression* ConditionalExpression::get_condition() 
		{
			return condition_.get();
		}

		const std::vector<std::unique_ptr<Expression>>& ConditionalExpression::get_if_body() const
		{
			return if_body_;
		}

		const std::vector<std::unique_ptr<Expression>>& ConditionalExpression::get_else_body() const
		{
			return else_body_;
		}

		bool ConditionalExpression::has_else_body() const
		{
			return else_body_.size() > 0;
		}

		void ConditionalExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
	}
}
