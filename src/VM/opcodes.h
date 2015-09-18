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

			// Float operations
			fconst,
			fadd,
			fmul,
			fsub,
			fdiv,

			// Char operations
			cconst,

			// Branching
			br_ieq,
			br_ineq,
			br_feq,
			br_fneq,

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
