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
			ieq,
			ineq,

			// Float operations
			fconst,
			fadd,
			fmul,
			fsub,
			fdiv,
			feq,
			fneq,

			// Char operations
			cconst,

			// Bool operations
			bconst,
			beq,
			bneq,

			// Branching
			br_ieq,
			br_ineq,
			br_feq,
			br_fneq,
			br_beq,
			br_bneq,

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
