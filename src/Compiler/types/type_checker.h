#pragma once

#include <memory>

#include "../ast/expression.h"
#include "../ast/char_literal_expression.h"
#include "../ast/integer_literal_expression.h"
#include "../ast/float_literal_expression.h"
#include "../ast/bool_literal_expression.h"
#include "../ast/identifier_expression.h"
#include "../ast/variable_declaration_expression.h"
#include "../ast/binary_operator_expression.h"
#include "../ast/prefix_operator_expression.h"
#include "elsa_type.h"
#include "../token.h"
#include "exceptions\parsing_exception.h"

namespace elsa {
	namespace compiler {

		class TypeChecker
		{
		public:
			static ElsaType* get_expression_type(Expression* expression);
			static ElsaType* get_type_from_token(TokenType type);

		private:
			template<typename TExpression>
			static bool is_of_type(Expression* exp);
		};

	}
}
