#pragma once

#include "expression.h"

namespace elsa {
	namespace compiler {

		class BoolLiteralExpression : public Expression
		{
		public:
			BoolLiteralExpression(bool value);

			bool get_value() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			bool value_;
		};
	}
}
