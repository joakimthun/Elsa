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
			null,

			// Functions
			call,
			ret,
			scall,
			fnconst,

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

			// Byte operations
			bconst,
			badd,
			bmul,
			bsub,
			bdiv,
			beq,
			bneq,
			blt,
			bgt,

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
			isl,
			isr,
			band,
			bor,

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
			br_beq,
			br_bneq,

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
