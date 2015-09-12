#pragma once

#include <cstdint>

namespace elsa {
	namespace vm {

		enum OpCode : int
		{
			nop = 0,
			halt,
			call_inst,
			call_static,
			ret,

			iconst,
			iadd,
			imul,
			isub,
			idiv,

			b_ieq,
			b_ineq,

			l_arg,
			l_local,

			s_local,

			print_ln

		};

	}
}
