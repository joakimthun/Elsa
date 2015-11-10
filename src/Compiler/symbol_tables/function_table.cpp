#include "function_table.h"

#include "../parsing/elsa_parser.h"

namespace elsa {
	namespace compiler {

		void FunctionTable::add_function(const std::wstring& name, ElsaParser* parser)
		{
			auto fs = new FunctionSymbol(name);
			add(name, fs);
			parser->set_current_function(fs);
		}

	}
}
