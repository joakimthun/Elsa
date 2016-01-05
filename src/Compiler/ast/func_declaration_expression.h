#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstddef>

#include "exceptions\elsa_exception.h"
#include "expression.h"
#include "argument_expression.h"
#include "../types/elsa_type.h"
#include "scoped_expression.h"


namespace elsa {
	namespace compiler {

		class FuncDeclarationExpression : public Expression, public ScopedExpression
		{
		public:
			FuncDeclarationExpression();

			std::unique_ptr<FuncDeclarationExpression> create_generic(const ElsaType* type);

			void add_args_expression(std::unique_ptr<ArgumentExpression> expression);
			void add_body_expression(std::unique_ptr<Expression> expression);

			void set_name(const std::wstring& name);
			void set_return_type(ElsaType* return_type);

			std::size_t get_num_args() const;
			std::size_t get_num_locals() const;
			void set_num_args(std::size_t num_args);
			void set_num_locals(std::size_t num_locals);
			void increment_num_args();
			void increment_num_locals();

			const std::wstring& get_name() const;
			const ElsaType* get_return_type() const;
			const std::vector<std::unique_ptr<Expression>>& get_body() const;
			const std::vector<std::unique_ptr<ArgumentExpression>>& get_args() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			void assert_is_impl();

			const FuncDeclarationExpression* impl_;
			std::wstring name_;
			std::unique_ptr<ElsaType> return_type_;
			std::vector<std::unique_ptr<ArgumentExpression>> args_;
			std::vector<std::unique_ptr<Expression>> body_;
			std::size_t num_locals_;
			std::size_t num_args_;
		};
	}
}
