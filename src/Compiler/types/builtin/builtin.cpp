#include "builtin.h"

namespace elsa {
	namespace compiler {

		void Builtin::init(VMProgram* program)
		{
			build_array(program);
		}

		void Builtin::build_array(VMProgram* program)
		{
			auto si = std::make_unique<StructInfo>(L"array");
		}

	}
}
