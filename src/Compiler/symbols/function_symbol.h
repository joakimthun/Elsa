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
			LocalTable& locals();

		private:
			std::wstring name_;
			LocalTable locals_;
		};

	}
}
