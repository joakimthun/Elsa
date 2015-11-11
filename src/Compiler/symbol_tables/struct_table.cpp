#include "struct_table.h"

namespace elsa {
	namespace compiler {

		StructTable::StructTable()
		{}

		void StructTable::add_struct(const std::wstring& name, StructDeclarationExpression* expression)
		{
			add(name, new StructSymbol(name, expression));
		}

	}
}
