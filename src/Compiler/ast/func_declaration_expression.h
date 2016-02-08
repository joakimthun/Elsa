#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstddef>
#include <algorithm>

#include "exceptions\elsa_exception.h"
#include "expression.h"
#include "argument_expression.h"
#include "variable_declaration_expression.h"
#include "../types/elsa_type.h"
#include "scoped_expression.h"


namespace elsa {
	namespace compiler {
		
		class ReturnExpression;

		struct ReturnExpressions
		{
			std::vector<ReturnExpression*> expressions;
			bool if_else_with_return;
		};

		class FuncDeclarationExpression : public ScopedExpression
		{
		public:
			FuncDeclarationExpression();
			FuncDeclarationExpression(ScopedExpression* parent);

			std::unique_ptr<FuncDeclarationExpression> create_generic(const ElsaType* type);

			void add_args_expression(std::unique_ptr<ArgumentExpression> expression);
			void add_args_expression_to_front(std::unique_ptr<ArgumentExpression> expression);
			void add_body_expression(std::unique_ptr<Expression> expression);

			void set_name(const std::wstring& name);
			void set_return_type(ElsaType* return_type);

			std::size_t get_num_args() const;
			std::size_t get_num_locals() const;
			void set_num_args(std::size_t num_args);
			void set_num_locals(std::size_t num_locals);
			void increment_num_args();
			void increment_num_locals();

			bool is_native() const;
			void set_is_native(bool native);
			bool built() const;
			void set_built(bool built);
			bool anonymous() const;
			void set_anonymous(bool anonymous);
			bool are_equal(const FuncDeclarationExpression* other) const;

			const std::wstring& get_name() const;
			const std::wstring get_type_name() const;
			const ElsaType* get_return_type() const;
			const std::vector<std::unique_ptr<Expression>>& get_body() const;
			const std::vector<std::unique_ptr<ArgumentExpression>>& get_args() const;

			ReturnExpressions get_return_expressions();

			std::vector<FuncDeclarationExpression*> get_nested_functions();

			void accept(ExpressionVisitor* visitor) override;

		private:
			void assert_is_impl();
			void get_return_expressions_internal(Expression* exp, ReturnExpressions& return_expressions);
			void get_nested_functions_internal(Expression* exp, std::vector<FuncDeclarationExpression*>& functions);
			int get_num_args_without_this_ptr(const FuncDeclarationExpression* fde) const;
			bool has_this_arg(const FuncDeclarationExpression* fde) const;

			const FuncDeclarationExpression* impl_;
			std::wstring name_;
			std::unique_ptr<ElsaType> return_type_;
			std::vector<std::unique_ptr<ArgumentExpression>> args_;
			std::vector<std::unique_ptr<Expression>> body_;
			std::size_t num_locals_;
			std::size_t num_args_;
			bool native_function_;
			bool built_;
			bool anonymous_;
		};
	}
}
