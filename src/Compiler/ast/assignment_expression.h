#pragma once

#include <memory>

#include "expression.h"
#include "../token.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class AssignmentExpression : public Expression
		{
		public:
			void set_left(std::unique_ptr<Expression> left);
			void set_right(std::unique_ptr<Expression> right);

			Expression* get_left() const;
			Expression* get_right() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::unique_ptr<Expression> left_;
			std::unique_ptr<Expression> right_;
		};
	}
}
