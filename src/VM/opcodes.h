#pragma once

#include <cstdint>

namespace elsa {
	namespace vm {

		enum OpCode : int
		{
			nop = 0,
			halt,
			call,
			ret,

			iconst,
			iadd,
			imul,
			isub,
			idiv,

			print

		};

	}
}
