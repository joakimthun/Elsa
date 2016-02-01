#include "func_declaration_expression.h"

#include "../code_gen/visitors/expression_visitor.h"
#include "return_expression.h"
#include "conditional_expression.h"
#include "loop_expression.h"

namespace elsa {
	namespace compiler {
		FuncDeclarationExpression::FuncDeclarationExpression(bool native_function)
			: ScopedExpression(nullptr, this),
			num_locals_(0),
			num_args_(0),
			impl_(nullptr),
			native_function_(native_function),
			built_(false),
			anonymous_(false)
		{
		}

		std::unique_ptr<FuncDeclarationExpression> FuncDeclarationExpression::create_generic(const ElsaType* type)
		{
			auto new_func = std::make_unique<FuncDeclarationExpression>();
			new_func->impl_ = this;
			new_func->name_ = name_;
			new_func->num_locals_ = num_locals_;
			new_func->num_args_ = num_args_;
			
			const auto field_type = return_type_->get_type() == ObjectType::Generic ? type : return_type_.get();
			new_func->return_type_ = std::make_unique<ElsaType>(field_type);

			for (const auto& arg : args_)
			{
				const auto arg_type = arg->get_type()->get_type() == ObjectType::Generic ? type : arg->get_type();
				new_func->args_.push_back(std::make_unique<ArgumentExpression>(arg->get_name(), arg_type));
			}

			return new_func;
		}

		void FuncDeclarationExpression::add_args_expression(std::unique_ptr<ArgumentExpression> expression)
		{
			assert_is_impl();
			args_.push_back(std::move(expression));
		}

		void FuncDeclarationExpression::add_body_expression(std::unique_ptr<Expression> expression)
		{
			assert_is_impl();
			body_.push_back(std::move(expression));
		}

		void FuncDeclarationExpression::set_name(const std::wstring& name)
		{
			assert_is_impl();
			name_ = name;
		}

		void FuncDeclarationExpression::set_return_type(ElsaType* return_type)
		{
			assert_is_impl();
			return_type_ = std::unique_ptr<ElsaType>(return_type);
		}

		std::size_t FuncDeclarationExpression::get_num_args() const
		{
			return num_args_;
		}

		std::size_t FuncDeclarationExpression::get_num_locals() const
		{
			return num_locals_;
		}

		void FuncDeclarationExpression::set_num_args(std::size_t num_args)
		{
			assert_is_impl();
			num_args_ = num_args;
		}

		void FuncDeclarationExpression::set_num_locals(std::size_t num_locals)
		{
			assert_is_impl();
			num_locals_ = num_locals;
		}

		void FuncDeclarationExpression::increment_num_args()
		{
			num_args_++;
		}

		void FuncDeclarationExpression::increment_num_locals()
		{
			num_locals_++;
		}

		bool FuncDeclarationExpression::is_native() const
		{
			return native_function_;
		}

		bool FuncDeclarationExpression::built() const
		{
			return built_;
		}

		void FuncDeclarationExpression::set_built(bool built)
		{
			built_ = built;
		}

		bool FuncDeclarationExpression::anonymous() const
		{
			return anonymous_;
		}

		void FuncDeclarationExpression::set_anonymous(bool anonymous)
		{
			anonymous_ = anonymous;
		}

		bool FuncDeclarationExpression::are_equal(const FuncDeclarationExpression* other) const
		{
			//if()

			return false;
		}

		const std::wstring& FuncDeclarationExpression::get_name() const
		{
			return name_;
		}

		const ElsaType* FuncDeclarationExpression::get_return_type() const
		{
			return return_type_.get();
		}

		const std::vector<std::unique_ptr<Expression>>& FuncDeclarationExpression::get_body() const
		{
			if (impl_ != nullptr)
				return impl_->get_body();

			return body_;
		}

		const std::vector<std::unique_ptr<ArgumentExpression>>& FuncDeclarationExpression::get_args() const
		{
			return args_;
		}

		ReturnExpressions FuncDeclarationExpression::get_return_expressions()
		{
			ReturnExpressions re;
			re.if_else_with_return = false;

			for (const auto& exp : body_)
			{
				get_return_expressions_internal(exp.get(), re);
			}

			return re;
		}

		std::vector<FuncDeclarationExpression*> FuncDeclarationExpression::get_nested_functions()
		{
			std::vector<FuncDeclarationExpression*> functions;

			for (const auto& exp : body_)
			{
				get_nested_functions_internal(exp.get(), functions);
			}

			return functions;
		}

		void FuncDeclarationExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}

		void FuncDeclarationExpression::assert_is_impl()
		{
			if (impl_ != nullptr)
				throw ElsaException("assert_is_impl");
		}

		void FuncDeclarationExpression::get_return_expressions_internal(Expression* exp, ReturnExpressions& return_expressions)
		{
			if (auto re = dynamic_cast<ReturnExpression*>(exp))
			{
				return_expressions.expressions.push_back(re);
			}
			else if (auto conde_exp = dynamic_cast<ConditionalExpression*>(exp))
			{
				auto if_with_return = false;
				auto else_with_return = false;
				for (const auto& ie : conde_exp->get_if_body())
				{
					if (auto ier = dynamic_cast<ReturnExpression*>(ie.get()))
					{
						if_with_return = true;
					}

					get_return_expressions_internal(ie.get(), return_expressions);
				}

				for (const auto& ee : conde_exp->get_else_body())
				{
					if (auto eer = dynamic_cast<ReturnExpression*>(ee.get()))
					{
						else_with_return = true;
					}

					get_return_expressions_internal(ee.get(), return_expressions);
				}

				return_expressions.if_else_with_return = if_with_return && else_with_return;
			}
			else if (auto loop_exp = dynamic_cast<LoopExpression*>(exp))
			{
				for (const auto& be : loop_exp->get_body())
				{
					get_return_expressions_internal(be.get(), return_expressions);
				}
			}
		}

		void FuncDeclarationExpression::get_nested_functions_internal(Expression* exp, std::vector<FuncDeclarationExpression*>& functions)
		{
			if (auto vde = dynamic_cast<VariableDeclarationExpression*>(exp))
			{
				if (auto fde = dynamic_cast<FuncDeclarationExpression*>(vde->get_expression()))
				{
					for (const auto& exp : fde->body_)
					{
						get_nested_functions_internal(exp.get(), functions);
					}

					functions.push_back(fde);
				}
			}
			else if (auto conde_exp = dynamic_cast<ConditionalExpression*>(exp))
			{
				for (const auto& ie : conde_exp->get_if_body())
				{
					get_nested_functions_internal(ie.get(), functions);
				}

				for (const auto& ee : conde_exp->get_else_body())
				{
					get_nested_functions_internal(ee.get(), functions);
				}
			}
			else if (auto loop_exp = dynamic_cast<LoopExpression*>(exp))
			{
				for (const auto& be : loop_exp->get_body())
				{
					get_nested_functions_internal(be.get(), functions);
				}
			}
		}
	}
}
