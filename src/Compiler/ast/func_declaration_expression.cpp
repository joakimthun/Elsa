#include "func_declaration_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {
		FuncDeclarationExpression::FuncDeclarationExpression()
			: ScopedExpression(nullptr, this),
			num_locals_(0),
			num_args_(0),
			impl_(nullptr)
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

		void FuncDeclarationExpression::accept(ExpressionVisitor* visitor)
		{
			visitor->visit(this);
		}
		void FuncDeclarationExpression::assert_is_impl()
		{
			if (impl_ != nullptr)
				throw ElsaException("assert_is_impl");
		}
	}
}
