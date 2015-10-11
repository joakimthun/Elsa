#pragma once

#include "expression.h"

namespace elsa {
	namespace compiler {

		class IntegerLiteralExpression : public Expression
		{
		public:
			IntegerLiteralExpression(int value);

			int get_value() const;

		private:
			int value_;
		};
	}
}
