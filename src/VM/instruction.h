#pragma once

#include "opcodes.h"
#include "types.h"

namespace elsa {
	namespace vm {

		typedef struct {
			OpCode oc;
			int r1;
			int r2;
			Object o;
		} Instruction;

	}
}
