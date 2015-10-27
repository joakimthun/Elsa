#pragma once

#include "expression.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class IntegerLiteralExpression : public Expression
		{
		public:
			IntegerLiteralExpression(int value);

			int get_value() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			int value_;
		};
	}
}
