#pragma once

#include <string>
#include <cstddef>

#include "../symbol_tables/local_table.h"
#include "../types/elsa_type.h"
#include "../ast/func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		class LocalSymbol;

		class FunctionSymbol
		{
		public:
			FunctionSymbol(const FuncDeclarationExpression* expression);

			const FuncDeclarationExpression* get_expression() const;

		private:
			std::wstring name_;
			const FuncDeclarationExpression* expression_;
		};

	}
}
