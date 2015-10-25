#pragma once

#include "expression.h"

namespace elsa {
	namespace compiler {

		class FloatLiteralExpression : public Expression
		{
		public:
			FloatLiteralExpression(float value);

			float get_value() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			float value_;
		};
	}
}
