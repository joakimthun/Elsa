#pragma once

#include "../parsing/ast/expression.h"
#include "elsa_type.h"

namespace elsa {
	namespace compiler {

		class TypeChecker
		{
		public:
			static ElsaType* get_expression_type(Expression* expression);
		};

	}
}
