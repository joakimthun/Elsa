#pragma once

#include <cstdint>

namespace elsa {
	namespace vm {

		enum OpCode : int
		{
			nop = 0,
			halt,

			// Functions
			call,
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

			// Structs
			new_struct,
			del_struct,
			l_field,
			s_field,

			// Arrays
			new_arr,
			l_ele,
			s_ele,

			// Misc
			print_ln

		};

	}
}
