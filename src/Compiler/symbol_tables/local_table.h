#pragma once

#include <cstddef>
#include <string>
#include <memory>
#include <vector>

#include "symbol_table.h"
#include "../symbols/local_symbol.h"
#include "exceptions\parsing_exception.h"
#include "constants\function_info.h"

namespace elsa {
	namespace compiler {

		class LocalTable : public SymbolTable<std::wstring, LocalSymbol>
		{
		public:
			LocalTable();

			void push_new_scope();
			void pop_current_scope();
			void push_current_scope(const std::wstring& name, const ElsaType& type);
			bool current_scope_has_entry(const std::wstring& name);
			const LocalSymbol* get_local(const std::wstring& name) const;
			bool scope_has_entry(std::size_t nesting, const std::wstring& name);
			const LocalSymbol* get_local(std::size_t nesting, const std::wstring& name) const;
			void increment_num_args();
			void increment_num_locals();
			void reset_num_locals_and_num_args();

		private:
			std::vector<std::unique_ptr<LocalTable>> local_table_;
			std::size_t num_args_;
			std::size_t num_locals_;
			std::size_t nesting_;
		};

	}
}
