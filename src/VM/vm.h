#pragma once

#include <cstddef>
#include <vector>
#include <iostream>
#include <memory>

#include "opcodes.h"
#include "object.h"
#include "call_stack.h"
#include "constants\constant_pool.h"
#include "constants\constant_entry.h"
#include "constants\function_entry.h"
#include "exceptions\elsa_exception.h"

namespace elsa {
	namespace vm {

		class  VM
		{
		public:
			VM(int* code, std::size_t length);
			~VM();

			void execute();
			void add_constant_entry(ConstantEntry* entry);
			void set_entry_point(std::size_t entry_point);
		private:
			void cycle();
			void print_line(const Object& o);

			int* code_;
			std::size_t code_length_;
			OpCode oc_;
			std::size_t pc_;
			int entry_point_;
			CallStack call_stack_;
			StackFrame* current_frame_;
			ConstantPool constant_pool_;
		};

	}
}
