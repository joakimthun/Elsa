#pragma once

#include <string>
#include <cstddef>

#include "../symbol_tables/local_table.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		class LocalSymbol;

		class FunctionSymbol
		{
		public:
			FunctionSymbol(const std::wstring& name);

			const std::wstring& get_name() const;
			bool has_local(const std::wstring& name) const;
			void add_local(const std::wstring& name, const ElsaType& type);
			LocalSymbol* get_local(const std::wstring& name);
		private:
			std::wstring name_;
			LocalTable locals_;
			std::size_t next_local_index_;
		};

	}
}
