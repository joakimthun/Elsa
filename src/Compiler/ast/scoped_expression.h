#pragma once

#include <string>

#include "expression.h"
#include "../symbol_tables/local_table.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class FuncDeclarationExpression;

		class ScopedExpression : public Expression
		{
		public:
			ScopedExpression(ScopedExpression* parent);

			LocalTable& locals();
			void add_arg(const std::wstring& name, const ElsaType& type);
			void add_arg(const std::wstring& name, const ElsaType& type, const StructDeclarationExpression* struct_expression);
			void add_local(const std::wstring& name, const ElsaType& type);
			void add_local(const std::wstring& name, const ElsaType& type, const StructDeclarationExpression* struct_expression);
			const LocalSymbol* get_local(const std::wstring& name);
			bool any_scope_has_local(const std::wstring& name);
			bool has_local(const std::wstring& name);
			std::size_t create_new_local();
			ScopedExpression* parent();

			void accept(ExpressionVisitor* visitor) override;

		private:
			FuncDeclarationExpression* get_root_scope();
			std::size_t add(const std::wstring& name, const ElsaType& type, const StructDeclarationExpression* struct_expression, LocalType local_type);
			ScopedExpression* parent_;
			LocalTable locals_;
		};
	}
}
