#pragma once

#include "exceptions/elsa_exception.h"

namespace elsa {
	namespace compiler {

		class ExpressionVisitor;

		class Expression
		{
		public:
			virtual ~Expression() {};
			virtual void accept(ExpressionVisitor* visitor) = 0;
		};

	}
}
