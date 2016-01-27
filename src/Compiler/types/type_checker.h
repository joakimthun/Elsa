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
#include "../ast/conditional_expression.h"
#include "../ast/loop_expression.h"
#include "../ast/return_expression.h"
#include "../ast/func_declaration_expression.h"
#include "../ast/array_declaration_expression.h"
#include "../ast/array_access_expression.h"
#include "../ast/array_initializer_list_expression.h"
#include "../ast/struct_declaration_expression.h"
#include "../ast/string_literal_expression.h"
#include "../ast/type_cast_expression.h"
#include "../ast/struct_initializer_list_expression.h"
#include "elsa_type.h"
#include "../token.h"
#include "..\exceptions\parsing_exception.h"


namespace elsa {
	namespace compiler {

		class ElsaParser;

		class TypeChecker
		{
		public:
			TypeChecker(ElsaParser* parser);

			ElsaType* get_expression_type(Expression* expression);
			ElsaType* get_type_from_token(Token* token);
			void assert_is_same_type(ObjectType t1, ObjectType t2);
			bool is_same_type(Expression* first, Expression* second);
			bool is_same_type(const ElsaType* first, const ElsaType* second);
			ElsaType* get_access_type(const ElsaType* type, const std::wstring& name, bool throw_invalid_exception = true);
			ElsaType* get_struct_type(const std::wstring& name);
			bool valid_assignment(AssignmentExpression* assignment_expression);
			bool valid_return_expression(Expression* expression);
			bool return_type_match(FuncDeclarationExpression* expression);
			template<typename TExpression>
			bool is_of_type(Expression* exp);
			bool is_boolean_operator(TokenType op);
			bool is_assignable(Expression* expression);

		private:
			ElsaParser* parser_;
		};

	}
}
