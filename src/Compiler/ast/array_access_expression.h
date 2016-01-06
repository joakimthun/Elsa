#pragma once

#include <memory>
#include <utility>
#include <cstddef>
#include <string>

#include "identifier_expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class ArrayAccessExpression : public Expression
		{
		public:
			void set_identifier_expression(std::unique_ptr<IdentifierExpression> identifier_expression);
			void set_index_expression(std::unique_ptr<Expression> expression);

			IdentifierExpression* get_identifier_expression() const;
			Expression* get_index_expression() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<IdentifierExpression> identifier_expression_;
			std::unique_ptr<Expression> index_expression_;
		};
	}
}