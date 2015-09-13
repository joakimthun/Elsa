#pragma once

#include <cstdint>

namespace elsa {
	namespace vm {

		enum OpCode : int
		{
			nop = 0,
			halt,

			// Functions
			call_inst,
			call_static,
			ret,

			// Integer operations
			iconst,
			iadd,
			imul,
			isub,
			idiv,

			// Branching
			b_ieq,
			b_ineq,

			// Locals and arguments
			l_arg,
			l_local,
			s_local,

			// Dynamic memory
			new_struct,
			del_struct,

			// Struct operations
			l_field,
			s_field,

			// Misc
			print_ln

		};

	}
}
