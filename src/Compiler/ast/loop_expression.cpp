#include "loop_expression.h"

namespace elsa {
	namespace compiler {

		void LoopExpression::set_variable_expression(std::unique_ptr<Expression> expression)
		{
			variable_expression_ = std::move(expression);
		}

		void LoopExpression::set_condition(std::unique_ptr<Expression> expression)
		{
			condition_ = std::move(expression);
		}

		void LoopExpression::set_post_expression(std::unique_ptr<Expression> expression)
		{
			post_expression_ = std::move(expression);
		}

		void LoopExpression::add_to_body(std::unique_ptr<Expression> expression)
		{
			body_.push_back(std::move(expression));
		}

		const Expression* LoopExpression::get_variable_expression() const
		{
			return variable_expression_.get();
		}

		const Expression* LoopExpression::get_condition() const
		{
			return condition_.get();
		}

		const Expression* LoopExpression::get_post_expression() const
		{
			return post_expression_.get();
		}

		const std::vector<std::unique_ptr<Expression>>& LoopExpression::get_body() const
		{
			return body_;
		}

		void LoopExpression::set_type()
		{

		}

		LoopType LoopExpression::get_type()
		{
			return type_;
		}

		void LoopExpression::accept(ExpressionVisitor* visitor)
		{

		}

	}
}
