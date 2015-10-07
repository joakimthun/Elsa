#pragma once

#include "expression.h"

namespace elsa {
	namespace compiler {

		class BoolLiteralExpression : public Expression
		{
		public:
			BoolLiteralExpression(bool value);

			bool get_value() const;

		private:
			bool value_;
		};
	}
}
