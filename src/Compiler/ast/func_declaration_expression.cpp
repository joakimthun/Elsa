#include "func_declaration_expression.h"

#include "../code_gen/visitors/expression_visitor.h"

namespace elsa {
	namespace compiler {
		FuncDeclarationExpression::FuncDeclarationExpression()
			: ScopedExpression(nullptr, this),
			num_locals_(0),
			num_args_(0)
		{
		}

		void FuncDeclarationExpression::add_args_expression(std::unique_ptr<ArgumentExpression> expression)
		{
			args_.push_back(std::move(expression));
		}

		void FuncDeclarationExpression::add_body_expression(std::unique_ptr<Expression> expression)
		{
			body_.push_back(std::move(expression));
		}

		void FuncDeclarationExpression::set_name(const std::wstring& name)
		{
			name_ = name;
		}

		void FuncDeclarationExpression::set_return_type(ElsaType* return_type)
		{
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
			num_args_ = num_args;
		}

		void FuncDeclarationExpression::set_num_locals(std::size_t num_locals)
		{
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
	}
}
