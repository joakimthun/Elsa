#pragma once

#include <string>

#include "../symbol_tables/local_table.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class FuncDeclarationExpression;

		class ScopedExpression
		{
		public:
			ScopedExpression(ScopedExpression* parent, FuncDeclarationExpression* root);

			LocalTable& locals();
			void add_local(const std::wstring& name, const ElsaType& type);
			const LocalSymbol* get_local(const std::wstring& name);
			bool any_scope_has_local(const std::wstring& name);
			bool has_local(const std::wstring& name);

		private:
			FuncDeclarationExpression* root_;
			ScopedExpression* parent_;
			LocalTable locals_;
		};
	}
}