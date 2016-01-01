#include "builtin.h"

namespace elsa {
	namespace compiler {

		void Builtin::init(VMProgram* program)
		{
			Array::init(program);
		}
		void Builtin::init(StructTable* table)
		{
			Array::init(table);
		}
	}
}
