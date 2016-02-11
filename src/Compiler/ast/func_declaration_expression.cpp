#include "func_declaration_expression.h"

#include "../expression_visitor.h"
#include "return_expression.h"
#include "conditional_expression.h"
#include "loop_expression.h"
#include "func_call_expression.h"

namespace elsa {
	namespace compiler {
		FuncDeclarationExpression::FuncDeclarationExpression()
			: ScopedExpression(nullptr),
			num_locals_(0),
			num_args_(0),
			impl_(nullptr),
			native_function_(false),
			built_(false),
			anonymous_(false)
		{
		}

		FuncDeclarationExpression::FuncDeclarationExpression(ScopedExpression* parent)
			: ScopedExpression(parent),
			num_locals_(0),
			num_args_(0),
			impl_(nullptr),
			native_function_(false),
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

		void FuncDeclarationExpression::add_args_expression_to_front(std::unique_ptr<ArgumentExpression> expression)
		{
			assert_is_impl();
			auto it = args_.begin();
			args_.insert(it, std::move(expression));
		}

		void FuncDeclarationExpression::add_body_expression(std::unique_ptr<Expression> expression)
		{
			assert_is_impl();
			body_.push_back(std::move(expression));
		}

		void FuncDeclarationExpression::add_body_expression_front(std::unique_ptr<Expression> expression)
		{
			assert_is_impl();
			auto it = body_.begin();
			body_.insert(it, std::move(expression));
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

		void FuncDeclarationExpression::set_is_native(bool native)
		{
			native_function_ = native;
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
			if (!this->return_type_->are_equal(other->return_type_.get()))
				return false;

			if (get_num_args_without_this_ptr(this) != get_num_args_without_this_ptr(other))
				return false;

			auto min_num_args = std::min(this->args_.size(), other->args_.size());
			auto this_offset = has_this_arg(this) ? 1 : 0;
			auto other_offset = has_this_arg(other) ? 1 : 0;
			for (auto i = 0; i < min_num_args; i++)
			{
				if (!this->args_[i + this_offset]->get_type()->are_equal(other->args_[i + other_offset]->get_type()))
					return false;
			}

			return true;
		}

		const std::wstring& FuncDeclarationExpression::get_name() const
		{
			return name_;
		}

		const std::wstring FuncDeclarationExpression::get_type_name() const
		{
			std::wstring type_name(L"func ");
			
			if (args_.size() > 0)
			{
				type_name.append(L"(");

				for (auto i = 0; i < args_.size(); i++)
				{
					type_name.append(args_[i]->get_type()->get_name());

					if(i != (args_.size() - 1))
						type_name.append(L", ");
				}

				type_name.append(L")");
			}

			if (return_type_->get_type() != ObjectType::Void)
			{
				type_name.append(L" : ");
				type_name.append(return_type_->get_name());
			}

			return type_name;
		}

		const ElsaType* FuncDeclarationExpression::get_return_type() const
		{
			return return_type_.get();
		}

		std::vector<std::unique_ptr<Expression>>& FuncDeclarationExpression::get_body()
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
			std::vector<ExpressionPair<FuncDeclarationExpression>> pairs;
			
			for (const auto& exp : body_)
			{
				NestedExpressionHelper::get_nested_expressions<FuncDeclarationExpression>(exp.get(), pairs, this);
			}
			
			for (const auto& exp : args_)
			{
				NestedExpressionHelper::get_nested_expressions<FuncDeclarationExpression>(exp.get(), pairs, this);
			}

			std::vector<FuncDeclarationExpression*> functions;
			for (auto pair : pairs)
			{
				functions.push_back(pair.expression);
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

		int FuncDeclarationExpression::get_num_args_without_this_ptr(const FuncDeclarationExpression * fde) const
		{
			auto args_size = static_cast<int>(fde->args_.size());

			if (fde->args_.size() == 0)
				return args_size;

			if(fde->args_[0]->get_name() == L"this")
				return args_size - 1;

			return args_size;
		}

		bool FuncDeclarationExpression::has_this_arg(const FuncDeclarationExpression* fde) const
		{
			if (fde->args_.size() == 0)
				return false;

			return fde->args_[0]->get_name() == L"this";
		}
	}
}
