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
				// Reset state for each function
				reset_state();

				set_captured_identifier_expressions(function);
				set_captured_struct_access_expressions(function);
				if (captured_identifier_expressions_.size() == 0 && captured_struct_access_expressions_.size() == 0)
					continue;

				set_captured_identifiers();

				auto struct_expression = StructFactory::create(parser_);
				capture_struct_ = struct_expression.get();
				create_capture_struct(function);

				for (auto& expression : function->get_body())
				{
					expression->accept(this);

					if (rewrite_variable_child())
					{
						expression.reset(next_variable_rewrite_.release());
					}
				}

				for (auto& member_func : struct_expression->get_functions())
				{
					inside_nested_func_ = true;

					for (auto& body_exp : member_func->get_body())
					{
						body_exp->accept(this);
					}

					inside_nested_func_ = false;
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
			for (auto& exp : expression->get_body())
			{
				exp->accept(this);
				
				if (rewrite_variable_child())
				{
					exp.reset(next_variable_rewrite_.release());
				}
				else if (rewrite_struct_access_child())
				{
					exp.reset(next_struct_access_rewrite_.release());
				}
			}
		}

		void ClosureRewriteVisitor::visit(VariableDeclarationExpression* expression)
		{
			if (dynamic_cast<FuncDeclarationExpression*>(expression->get_expression()))
			{
				auto member_fde = rewrite_as_member_function(expression);
				point_variable_expression_to_member_func(expression, member_fde);
			}

			if (captured_in_closure(expression->get_name()))
			{
				rewrite_as_assignment_expression(expression);
			}
		}

		void ClosureRewriteVisitor::visit(BinaryOperatorExpression* expression)
		{
			expression->get_left()->accept(this);
			if (rewrite_identifier_child())
			{
				expression->set_left(std::move(next_identifier_rewrite_));
			}
			else if (rewrite_struct_access_child())
			{
				expression->set_left(std::move(next_struct_access_rewrite_));
			}

			expression->get_right()->accept(this);
			if (rewrite_identifier_child())
			{
				expression->set_right(std::move(next_identifier_rewrite_));
			}
			else if (rewrite_struct_access_child())
			{
				expression->set_right(std::move(next_struct_access_rewrite_));
			}
		}

		void ClosureRewriteVisitor::visit(IntegerLiteralExpression* expression)
		{
		}

		void ClosureRewriteVisitor::visit(IdentifierExpression* expression)
		{
			if (captured_in_closure(expression->get_name()))
			{
				rewrite_captured_identifier_expression(expression);
			}
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
			if (expression->get_base() != nullptr && captured_in_closure(expression->get_base()->get_name()))
			{
				rewrite_captured_struct_access_expression(expression);
			}
		}

		void ClosureRewriteVisitor::visit(AssignmentExpression* expression)
		{
			expression->get_left()->accept(this);
			if (rewrite_identifier_child())
			{
				expression->set_left(std::move(next_identifier_rewrite_));
			}
			else if (rewrite_struct_access_child())
			{
				expression->set_left(std::move(next_struct_access_rewrite_));
			}

			expression->get_right()->accept(this);
			if (rewrite_identifier_child())
			{
				expression->set_right(std::move(next_identifier_rewrite_));
			}
			else if (rewrite_struct_access_child())
			{
				expression->set_right(std::move(next_struct_access_rewrite_));
			}
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
			expression->get_expression()->accept(this);
			if (rewrite_identifier_child())
			{
				expression->set_expression(std::move(next_identifier_rewrite_));
			}
			else if (rewrite_struct_access_child())
			{
				expression->set_expression(std::move(next_struct_access_rewrite_));
			}
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

		void ClosureRewriteVisitor::visit(GroupedExpression* expression)
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

		void ClosureRewriteVisitor::create_capture_struct(FuncDeclarationExpression* fde)
		{
			capture_variable_name_ = StringUtil::create_random_string(25);

			auto field_index = add_capured_identifiers_as_fields();
			add_capured_structs_as_fields(field_index);

			auto create_capture_struct = std::make_unique<CreateStructExpression>(capture_struct_->get_name(), parser_->type_checker().get_struct_type(capture_struct_->get_name()));

			auto capture_struct_type = std::unique_ptr<ElsaType>(parser_->type_checker().get_expression_type(create_capture_struct.get()));
			fde->add_local(capture_variable_name_, *capture_struct_type, capture_struct_);

			auto capture_varaible = std::make_unique<VariableDeclarationExpression>(capture_variable_name_, capture_struct_type.release(), std::move(create_capture_struct));
			fde->add_body_expression_front(std::move(capture_varaible));
		}

		std::size_t ClosureRewriteVisitor::add_capured_identifiers_as_fields()
		{
			std::size_t field_index = 0;
			for (auto identifier : captured_identifier_expressions_)
			{
				capture_struct_->add_field_expression(std::make_unique<FieldExpression>(identifier.expression->get_name(), new ElsaType(identifier.expression->get_type()), field_index++));
			}

			return field_index;
		}

		void ClosureRewriteVisitor::add_capured_structs_as_fields(std::size_t field_index)
		{
			for (auto struct_access : captured_struct_access_expressions_)
			{
				capture_struct_->add_field_expression(std::make_unique<FieldExpression>(struct_access.expression->get_base()->get_name(), new ElsaType(struct_access.expression->get_base()->get_type()), field_index++));
			}
		}

		void ClosureRewriteVisitor::set_captured_identifier_expressions(FuncDeclarationExpression* expression)
		{
			auto identifier_expressions = NestedExpressionHelper::get_nested_expressions<IdentifierExpression>(expression);

			for (auto pair : identifier_expressions)
			{
				if (pair.expression->get_from_closure())
				{
					captured_identifier_expressions_.push_back(pair);
				}
			}
		}

		void ClosureRewriteVisitor::set_captured_struct_access_expressions(FuncDeclarationExpression* expression)
		{
			auto struct_access_expressions = NestedExpressionHelper::get_nested_expressions<StructAccessExpression>(expression);

			for (auto pair : struct_access_expressions)
			{
				if (pair.expression->get_base() != nullptr && pair.expression->get_base()->get_from_closure())
				{
					captured_struct_access_expressions_.push_back(pair);
				}
			}
		}

		void ClosureRewriteVisitor::set_captured_identifiers()
		{
			for (auto& id_exp : captured_identifier_expressions_)
			{
				captured_identifiers_.push_back(id_exp.expression->get_name());
			}

			for (auto& str_exp : captured_struct_access_expressions_)
			{
				if (str_exp.expression->get_base() != nullptr)
				{
					captured_identifiers_.push_back(str_exp.expression->get_base()->get_name());
				}
			}
		}

		FuncDeclarationExpression* ClosureRewriteVisitor::rewrite_as_member_function(VariableDeclarationExpression* vde)
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

		void ClosureRewriteVisitor::rewrite_captured_identifier_expression(IdentifierExpression* identifier_expression)
		{
			auto sa_exp = std::make_unique<StructAccessExpression>();
			auto id_exp = std::make_unique<IdentifierExpression>(get_base_identifier_name());

			id_exp->set_type(parser_->type_checker().get_expression_type(capture_struct_));
			sa_exp->set_base(std::move(id_exp));

			auto fa_exp = std::make_unique<FieldAccessExpression>(identifier_expression->get_name());
			fa_exp->set_type(new ElsaType(identifier_expression->get_type()));
			sa_exp->add_expression(fa_exp.release());

			next_identifier_rewrite_ = std::move(sa_exp);
		}

		void ClosureRewriteVisitor::rewrite_captured_struct_access_expression(StructAccessExpression* struct_access_expression)
		{
			auto sa_exp = std::make_unique<StructAccessExpression>();
			auto id_exp = std::make_unique<IdentifierExpression>(get_base_identifier_name());

			id_exp->set_type(parser_->type_checker().get_expression_type(capture_struct_));
			sa_exp->set_base(std::move(id_exp));

			auto fa_exp = std::make_unique<FieldAccessExpression>(struct_access_expression->get_base()->get_name());
			fa_exp->set_type(new ElsaType(struct_access_expression->get_base()->get_type()));
			sa_exp->add_expression(fa_exp.release());

			for (auto& exp : struct_access_expression->get_expressions())
			{
				sa_exp->add_expression(exp.release());
			}

			next_struct_access_rewrite_ = std::move(sa_exp);
		}

		void ClosureRewriteVisitor::rewrite_as_assignment_expression(VariableDeclarationExpression* vde)
		{
			auto sa_exp = std::make_unique<StructAccessExpression>();

			auto id_exp = std::make_unique<IdentifierExpression>(capture_variable_name_);
			id_exp->set_type(parser_->type_checker().get_expression_type(capture_struct_));
			sa_exp->set_base(std::move(id_exp));

			auto fa_exp = std::make_unique<FieldAccessExpression>(vde->get_name());
			fa_exp->set_type(new ElsaType(vde->get_type()));
			sa_exp->add_expression(fa_exp.release());

			next_variable_rewrite_ = std::make_unique<AssignmentExpression>();
			next_variable_rewrite_->set_left(std::move(sa_exp));
			next_variable_rewrite_->set_right(vde->move_expression());
		}

		bool ClosureRewriteVisitor::rewrite_identifier_child()
		{
			return next_identifier_rewrite_.get() != nullptr;
		}

		bool ClosureRewriteVisitor::rewrite_variable_child()
		{
			return next_variable_rewrite_.get() != nullptr;
		}

		bool ClosureRewriteVisitor::rewrite_struct_access_child()
		{
			return next_struct_access_rewrite_.get() != nullptr;
		}

		void ClosureRewriteVisitor::reset_state()
		{
			captured_identifier_expressions_.clear();
			captured_struct_access_expressions_.clear();
			next_identifier_rewrite_.reset(nullptr);
			next_variable_rewrite_.reset(nullptr);
			next_struct_access_rewrite_.reset(nullptr);
			inside_nested_func_ = false;
		}

		bool ClosureRewriteVisitor::captured_in_closure(const std::wstring& name)
		{
			for (const auto& id : captured_identifiers_)
			{
				if (id == name)
					return true;
			}

			return false;
		}

		std::wstring ClosureRewriteVisitor::get_base_identifier_name()
		{
			if (inside_nested_func_)
				return L"this";

			return capture_variable_name_;
		}
	}
}