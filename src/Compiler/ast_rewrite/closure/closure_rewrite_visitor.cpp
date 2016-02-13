#include "closure_rewrite_visitor.h"

#include "../../helpers/nested_expression_helper.h"
#include "../../helpers/struct_factory.h"
#include "util\string_util.h"
#include "../../types/elsa_type.h"
#include "../../ast/struct_access_expression.h"
#include "../../ast/create_struct_expression.h"
#include "../../ast/struct_declaration_expression.h"

namespace elsa {
	namespace compiler {

		ClosureRewriteVisitor::ClosureRewriteVisitor(Program* program, ElsaParser* parser)
			:
			program_(program),
			parser_(parser),
			capture_struct_(nullptr)
		{
		}

		void ClosureRewriteVisitor::rewrite()
		{
			auto functions = program_->get_statements_of_type<FuncDeclarationExpression>();
			
			for (auto function : functions)
			{
				auto identifier_expressions = identifier_expressions_in_closure(function);
				if (identifier_expressions.size() == 0)
					continue;
				
				auto struct_expression = StructFactory::create(parser_);
				capture_struct_ = struct_expression.get();
				create_capture_struct(function, identifier_expressions);

				for (auto& expression : function->get_body())
				{
					expression->accept(this);
				}

				for (auto pair : identifier_expressions)
				{
					rewrite_captured_identifier_expression(pair.expression, pair.parent);
				}
			
				add_statement(std::move(struct_expression));
			}
		}

		std::vector<std::unique_ptr<Expression>>& ClosureRewriteVisitor::get_new_statements()
		{
			return statements_;
		}

		void ClosureRewriteVisitor::visit(FuncDeclarationExpression* expression)
		{
			//for (auto& exp : expression->get_body())
			//{
			//
			//}
		}

		void ClosureRewriteVisitor::visit(VariableDeclarationExpression* expression)
		{
			if (auto fde = dynamic_cast<FuncDeclarationExpression*>(expression->get_expression()))
			{
				auto member_fde = rewrite_as_member_function(expression, fde);
				point_variable_expression_to_member_func(expression, member_fde);
			}
		}

		void ClosureRewriteVisitor::visit(BinaryOperatorExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(IntegerLiteralExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(IdentifierExpression* expression)
		{
			//if(expression->get_from_closure())
			//	rewrite_captured_identifier_expression(expression);
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

		void ClosureRewriteVisitor::create_capture_struct(FuncDeclarationExpression* fde, std::vector<ExpressionPair<IdentifierExpression>>& identifier_expressions)
		{
			capture_variable_name_ = StringUtil::create_random_string(25);

			add_capured_identifiers_as_fields(identifier_expressions);

			auto create_capture_struct = std::make_unique<CreateStructExpression>(capture_struct_->get_name(), parser_->type_checker().get_struct_type(capture_struct_->get_name()));

			auto capture_struct_type = std::unique_ptr<ElsaType>(parser_->type_checker().get_expression_type(create_capture_struct.get()));
			fde->add_local(capture_variable_name_, *capture_struct_type, capture_struct_);

			auto capture_varaible = std::make_unique<VariableDeclarationExpression>(capture_variable_name_, capture_struct_type.release(), std::move(create_capture_struct));
			fde->add_body_expression_front(std::move(capture_varaible));
		}

		void ClosureRewriteVisitor::add_capured_identifiers_as_fields(std::vector<ExpressionPair<IdentifierExpression>>& identifiers)
		{
			std::size_t field_index = 0;
			for (auto identifier : identifiers)
			{
				capture_struct_->add_field_expression(std::make_unique<FieldExpression>(identifier.expression->get_name(), new ElsaType(identifier.expression->get_type()), field_index++));
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

		FuncDeclarationExpression* ClosureRewriteVisitor::rewrite_as_member_function(VariableDeclarationExpression* vde, FuncDeclarationExpression* fde)
		{
			auto member_func = std::unique_ptr<FuncDeclarationExpression>(static_cast<FuncDeclarationExpression*>(vde->release_expression()));

			// Add a this pointer as the first argument
			auto arg = std::make_unique<ArgumentExpression>(ArgumentType::InstRef);
			arg->set_type(parser_->type_checker().get_expression_type(capture_struct_));
			arg->set_name(L"this");
			member_func->add_arg(arg->get_name(), arg->get_type());
			member_func->add_args_expression_to_front(std::move(arg));

			auto member_fde = member_func.get();

			capture_struct_->add_member_function(std::move(member_func));

			return member_fde;
		}

		void ClosureRewriteVisitor::point_variable_expression_to_member_func(VariableDeclarationExpression* vde, FuncDeclarationExpression* member_fde)
		{
			auto sa_exp = std::make_unique<StructAccessExpression>();
			auto id_exp = std::make_unique<IdentifierExpression>(capture_variable_name_);

			id_exp->set_type(parser_->type_checker().get_expression_type(capture_struct_));
			sa_exp->set_base(std::move(id_exp));

			auto member_id_exp = std::make_unique<IdentifierExpression>(member_fde->get_name());
			member_id_exp->set_type(new ElsaType(member_fde));
			sa_exp->add_expression(member_id_exp.release());

			vde->set_expression(std::move(sa_exp));
		}

		void ClosureRewriteVisitor::rewrite_captured_identifier_expression(IdentifierExpression* identifier_expression, Expression* parent)
		{
			auto sa_exp = std::make_unique<StructAccessExpression>();
			auto id_exp = std::make_unique<IdentifierExpression>(L"this");

			id_exp->set_type(parser_->type_checker().get_expression_type(capture_struct_));
			sa_exp->set_base(std::move(id_exp));

			auto fa_exp = std::make_unique<FieldAccessExpression>(identifier_expression->get_name());
			fa_exp->set_type(new ElsaType(identifier_expression->get_type()));
			sa_exp->add_expression(fa_exp.release());

			if (auto boe = dynamic_cast<BinaryOperatorExpression*>(parent))
			{
				boe->set_left(std::move(sa_exp));
			}
		}
	}
}