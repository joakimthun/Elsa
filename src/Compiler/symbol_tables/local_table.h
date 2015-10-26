#pragma once

#include <cstddef>
#include <string>
#include <memory>

#include "symbol_table.h"
#include "../symbols/local_symbol.h"

namespace elsa {
	namespace compiler {

		class LocalTable : public SymbolTable<std::wstring, LocalSymbol>
		{
		public:
			LocalTable()
				:
				next_index_(0)
			{}

			std::size_t get_next_index() 
			{
				return next_index_++;
			}

		private:
			std::size_t next_index_;
		};

	}
}
