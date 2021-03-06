#pragma once

#include <string>
#include <memory>

#include "symbol_table.h"
#include "../symbols/function_symbol.h"

namespace elsa {
	namespace compiler {

		class FuncDeclarationExpression;

		class FunctionTable : public SymbolTable<std::wstring, FunctionSymbol>
		{
		public:
			void add_function(const FuncDeclarationExpression* expression);
		};

	}
}
