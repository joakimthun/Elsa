#include "closure_rewriter.h"

#include "../ast_rewrite_expression_visitor.h"
#include "../../helpers/nested_expression_helper.h"

namespace elsa {
	namespace compiler {

		void ClosureRewriter::rewrite(ASTRewriteExpressionVisitor* visitor, FuncDeclarationExpression* expression)
		{
			auto nested_functions = NestedExpressionHelper::get_nested_expressions<FuncDeclarationExpression>(expression);
			if (nested_functions.size() == 0)
				return;

			auto identifier_expressions = identifier_expressions_in_closure(expression);
			if (identifier_expressions.size() == 0)
				return;

			auto struct_expression = StructFactory::create(visitor->parser());

			add_capured_identifiers_as_fields(identifier_expressions, struct_expression.get());
			add_anonymous_functions_as_members(nested_functions, struct_expression.get(), visitor);

			visitor->add_statement(std::move(struct_expression));
		}

		void ClosureRewriter::add_capured_identifiers_as_fields(std::vector<ExpressionPair<IdentifierExpression>>& identifiers, StructDeclarationExpression* struct_exp)
		{
			std::size_t field_index = 0;
			for (auto identifier : identifiers)
			{
				struct_exp->add_field_expression(std::make_unique<FieldExpression>(identifier.expression->get_name(), new ElsaType(identifier.expression->get_type()), field_index++));
			}
		}

		void ClosureRewriter::add_anonymous_functions_as_members(std::vector<ExpressionPair<FuncDeclarationExpression>>& pairs, StructDeclarationExpression* struct_exp, ASTRewriteExpressionVisitor* visitor)
		{
			for (auto& pair : pairs)
			{
				rewrite_as_member_function(pair, struct_exp, visitor);
			}
		}

		std::vector<ExpressionPair<IdentifierExpression>> ClosureRewriter::identifier_expressions_in_closure(FuncDeclarationExpression* expression)
		{
			auto identifier_expressions = NestedExpressionHelper::get_nested_expressions<IdentifierExpression>(expression);
			auto in_closure = std::vector<ExpressionPair<IdentifierExpression>>();

			for (auto pair : identifier_expressions)
			{
				if (pair.expression->get_from_closure())
				{
					in_closure.push_back(pair);
				}
			}

			return in_closure;
		}

		void ClosureRewriter::rewrite_as_member_function(ExpressionPair<FuncDeclarationExpression> pair, StructDeclarationExpression* struct_exp, ASTRewriteExpressionVisitor* visitor)
		{
			if (auto vde = dynamic_cast<VariableDeclarationExpression*>(pair.parent))
			{
				if (dynamic_cast<FuncDeclarationExpression*>(vde->get_expression()))
				{
					auto member_func = std::unique_ptr<FuncDeclarationExpression>(static_cast<FuncDeclarationExpression*>(vde->release_expression()));

					// Add a this pointer as the first argument
					auto arg = std::make_unique<ArgumentExpression>(ArgumentType::InstRef);
					arg->set_type(visitor->parser()->type_checker().get_expression_type(struct_exp));
					arg->set_name(L"this");
					member_func->add_arg(arg->get_name(), arg->get_type());
					member_func->add_args_expression_to_front(std::move(arg));

					struct_exp->add_member_function(std::move(member_func));
				}
			}
		}
	}
}
