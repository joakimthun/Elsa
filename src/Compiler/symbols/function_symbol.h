#pragma once

#include <string>
#include "../symbol_tables/local_table.h"

namespace elsa {
	namespace compiler {

		class LocalSymbol;

		class FunctionSymbol
		{
		public:
			FunctionSymbol(const std::wstring& name);

			const std::wstring& get_name() const;
			bool has_local(const std::wstring& name);
			LocalSymbol* get_local(const std::wstring& name);
		private:
			std::wstring name_;
			LocalTable locals_;
		};

	}
}
