#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <algorithm>

#include "../../helpers/struct_factory.h"
#include "../../ast/func_declaration_expression.h"
#include "../../ast/binary_operator_expression.h"
#include "../../ast/integer_literal_expression.h"
#include "../../ast/identifier_expression.h"
#include "../../ast/struct_access_expression.h"
#include "../../ast/variable_declaration_expression.h"

namespace elsa {
	namespace compiler {

		class ASTRewriteExpressionVisitor;

		class ClosureRewriter
		{
		public:
			static void rewrite(ASTRewriteExpressionVisitor* visitor, FuncDeclarationExpression* expression);

		private:
			static void add_capured_identifiers_as_fields(std::vector<ExpressionPair<IdentifierExpression>>& identifiers, StructDeclarationExpression* struct_exp);
			static void add_anonymous_functions_as_members(std::vector<ExpressionPair<FuncDeclarationExpression>>& pairs, StructDeclarationExpression* struct_exp, ASTRewriteExpressionVisitor* visitor);
			static std::vector<ExpressionPair<IdentifierExpression>> identifier_expressions_in_closure(FuncDeclarationExpression* expression);
			static void rewrite_as_member_function(ExpressionPair<FuncDeclarationExpression> pair, StructDeclarationExpression* struct_exp, ASTRewriteExpressionVisitor* visitor);
		};

	}
}