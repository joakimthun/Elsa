#pragma once

#include <memory>
#include <string>

#include "../ast/expression.h"
#include "../ast/char_literal_expression.h"
#include "../ast/integer_literal_expression.h"
#include "../ast/float_literal_expression.h"
#include "../ast/bool_literal_expression.h"
#include "../ast/identifier_expression.h"
#include "../ast/variable_declaration_expression.h"
#include "../ast/binary_operator_expression.h"
#include "../ast/prefix_operator_expression.h"
#include "../ast/field_access_expression.h"
#include "../ast/create_struct_expression.h"
#include "../ast/struct_access_expression.h"
#include "../ast/assignment_expression.h"
#include "../ast/argument_expression.h"
#include "elsa_type.h"
#include "../token.h"
#include "exceptions\parsing_exception.h"


namespace elsa {
	namespace compiler {

		class ElsaParser;

		class TypeChecker
		{
		public:
			TypeChecker(ElsaParser* parser);

			ElsaType* get_expression_type(Expression* expression);
			ElsaType* get_type_from_token(Token* token);
			void assert_is_same_type(OType t1, OType t2);
			bool is_same_type(Expression* first, Expression* second);
			ElsaType* get_field_type(const StructDeclarationExpression* struct_expression, const FieldAccessExpression* field);
			ElsaType* get_struct_type(const std::wstring& name);
			bool valid_assignment(AssignmentExpression* assignment_expression);
			template<typename TExpression>
			bool is_of_type(Expression* exp);

		private:
			ElsaParser* parser_;
		};

	}
}
