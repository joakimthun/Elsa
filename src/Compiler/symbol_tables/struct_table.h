#pragma once

#include <cstddef>
#include <string>
#include <memory>

#include "symbol_table.h"
#include "../symbols/struct_symbol.h"

namespace elsa {
	namespace compiler {

		class StructTable : public SymbolTable<std::wstring, StructSymbol>
		{
		public:
			StructTable();
			void add_struct(const std::wstring& name);
		};

	}
}
