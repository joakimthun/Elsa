#pragma once

#include <cstdint>

namespace elsa {

		enum OpCode : int
		{
			// Misc
			nop = 0,
			halt,
			pop,
			t_cast,

			// Functions
			call,
			ret,
			scall,

			// Integer operations
			iconst,
			iadd,
			imul,
			isub,
			idiv,
			ieq,
			ineq,
			ilt,
			igt,

			// Float operations
			fconst,
			fadd,
			fmul,
			fsub,
			fdiv,
			feq,
			fneq,
			flt,
			fgt,

			// Char operations
			cconst,
			ceq,
			cneq,

			// Bitwise operations
			iand,
			ior,

			// String operations
			sconst,

			// Branching
			br,
			br_ieq,
			br_ineq,
			br_feq,
			br_fneq,
			br_ceq,
			br_cneq,

			// Locals and arguments
			l_arg,
			l_local,
			s_local,

			// Structs
			new_struct,
			l_field,
			s_field,

			// Arrays
			new_arr,
			len_arr,
			c_arr,
			l_ele,
			s_ele,
			a_ele,
			p_ele,
			r_ele,

			// Interop
			ncall,
		};

}
