#pragma once

#include <cstddef>
#include <string>
#include <memory>
#include <vector>

#include "symbol_table.h"
#include "../symbols/local_symbol.h"

namespace elsa {
	namespace compiler {

		class LocalTable : public SymbolTable<std::wstring, LocalSymbol>
		{
		};

	}
}
