#include "closure_rewrite_visitor.h"

#include "../../helpers/nested_expression_helper.h"
#include "../../helpers/struct_factory.h"

namespace elsa {
	namespace compiler {

		ClosureRewriteVisitor::ClosureRewriteVisitor(Program* program, ElsaParser* parser)
			:
			program_(program),
			parser_(parser)
		{
		}

		void ClosureRewriteVisitor::rewrite()
		{
			auto functions = program_->get_statements_of_type<FuncDeclarationExpression>();
			
			for (auto function : functions)
			{
				auto identifier_expressions = identifier_expressions_in_closure(function);
				if (identifier_expressions.size() == 0)
					return;
			
				auto struct_expression = StructFactory::create(parser_);
			
				add_capured_identifiers_as_fields(identifier_expressions, struct_expression.get());
				//add_anonymous_functions_as_members(nested_functions, struct_expression.get());
			
				add_statement(std::move(struct_expression));
			
				function->add_body_expression_front(std::make_unique<CreateStructExpression>(struct_expression->get_name(), parser_->type_checker().get_struct_type(struct_expression->get_name())));
			}
		}

		std::vector<std::unique_ptr<Expression>>& ClosureRewriteVisitor::get_new_statements()
		{
			return statements_;
		}

		void ClosureRewriteVisitor::visit(FuncDeclarationExpression* expression)
		{

		}

		void ClosureRewriteVisitor::visit(VariableDeclarationExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(BinaryOperatorExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(IntegerLiteralExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(IdentifierExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(FloatLiteralExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(CharLiteralExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(StructDeclarationExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(CreateStructExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(StructAccessExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(AssignmentExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(FuncCallExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(BoolLiteralExpression * expression)
		{
		}

		void ClosureRewriteVisitor::visit(ConditionalExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(LoopExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(PostfixOperatorExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(ReturnExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(ArrayDeclarationExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(ArrayAccessExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(ArrayInitializerListExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(StringLiteralExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(TypeCastExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(StructInitializerListExpression* expression)
		{
		}

		ElsaParser* ClosureRewriteVisitor::parser()
		{
			return parser_;
		}

		void ClosureRewriteVisitor::add_statement(std::unique_ptr<Expression> node)
		{
			statements_.push_back(std::move(node));
		}

		void ClosureRewriteVisitor::add_capured_identifiers_as_fields(std::vector<ExpressionPair<IdentifierExpression>>& identifiers, StructDeclarationExpression* struct_exp)
		{
			std::size_t field_index = 0;
			for (auto identifier : identifiers)
			{
				struct_exp->add_field_expression(std::make_unique<FieldExpression>(identifier.expression->get_name(), new ElsaType(identifier.expression->get_type()), field_index++));
			}
		}

		void ClosureRewriteVisitor::add_anonymous_functions_as_members(std::vector<ExpressionPair<FuncDeclarationExpression>>& pairs, StructDeclarationExpression* struct_exp)
		{
			for (auto& pair : pairs)
			{
				rewrite_as_member_function(pair, struct_exp);
			}
		}

		std::vector<ExpressionPair<IdentifierExpression>> ClosureRewriteVisitor::identifier_expressions_in_closure(FuncDeclarationExpression* expression)
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

		void ClosureRewriteVisitor::rewrite_as_member_function(ExpressionPair<FuncDeclarationExpression> pair, StructDeclarationExpression* struct_exp)
		{
			if (auto vde = dynamic_cast<VariableDeclarationExpression*>(pair.parent))
			{
				if (dynamic_cast<FuncDeclarationExpression*>(vde->get_expression()))
				{
					auto member_func = std::unique_ptr<FuncDeclarationExpression>(static_cast<FuncDeclarationExpression*>(vde->release_expression()));

					// Add a this pointer as the first argument
					auto arg = std::make_unique<ArgumentExpression>(ArgumentType::InstRef);
					arg->set_type(parser_->type_checker().get_expression_type(struct_exp));
					arg->set_name(L"this");
					member_func->add_arg(arg->get_name(), arg->get_type());
					member_func->add_args_expression_to_front(std::move(arg));

					struct_exp->add_member_function(std::move(member_func));
				}
			}
		}

	}
}