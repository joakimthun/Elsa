#pragma once

#include "expression.h"

namespace elsa {
	namespace compiler {

		class CharLiteralExpression : public Expression
		{
		public:
			CharLiteralExpression(wchar_t value);

			wchar_t get_value() const;

		private:
			wchar_t value_;
		};
	}
}
