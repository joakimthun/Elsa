#pragma once

#include "../parsing/ast/expression.h"
#include "elsa_type.h"
#include "../lexing/token.h"
#include "exceptions\parsing_exception.h"

namespace elsa {
	namespace compiler {

		class TypeChecker
		{
		public:
			static ElsaType* get_expression_type(Expression* expression);
			static ElsaType* get_type_from_token(TokenType type);
		};

	}
}
