#pragma once

#include <stdint.h>

#include "expression.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class ByteLiteralExpression : public Expression
		{
		public:
			ByteLiteralExpression(uint8_t value);

			uint8_t get_value() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			uint8_t value_;
		};
	}
}
