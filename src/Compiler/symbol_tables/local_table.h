#pragma once

#include <string>
#include <memory>

#include "symbol_table.h"
#include "../symbols/local_symbol.h"

namespace elsa {
	namespace compiler {

		class LocalTable : public SymbolTable<std::wstring, LocalSymbol>
		{
		};

	}
}
