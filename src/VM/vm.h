#pragma once

#include <cstddef>
#include <vector>
#include <iostream>

#include "opcodes.h"
#include "object.h"
#include "call_stack.h"

namespace elsa {
	namespace vm {

		class  VM
		{
		public:
			VM(int* code, std::size_t length);
			~VM();

			void execute();
		private:
			void cycle();

			int* code_;
			std::size_t code_length_;
			OpCode oc_;
			std::size_t pc_;
			CallStack call_stack_;
			StackFrame* current_frame_;
		};

	}
}
