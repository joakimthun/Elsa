#pragma once

#include <cstddef>
#include <vector>
#include <iostream>
#include <memory>

#include "opcodes.h"
#include "types\otype.h"
#include "types\object.h"
#include "call_stack.h"
#include "memory\heap.h"
#include "constants\constant_pool.h"
#include "constants\constant_entry.h"
#include "constants\function_info.h"
#include "exceptions\runtime_exception.h"
#include "GC\gc.h"

namespace elsa {
	namespace vm {

		class  VM
		{
		public:
			VM();
			VM(const std::vector<int>& code);
			~VM();

			void execute();
			void execute_one();
			void skip_one();
			void set_program(const std::vector<int>& code);
			void add_constant_entry(ConstantEntry* entry);
			void set_entry_point(std::size_t entry_point);
			Object eval_stack_top() const;
			std::size_t get_pc() const;
			GCResult gc_collect();

		private:
			void cycle();
			void push_main();
			void next_opcode();
			void print_line(const Object& o);

			std::vector<int> code_;
			std::size_t code_length_;
			OpCode oc_;
			std::size_t pc_;
			int entry_point_;
			CallStack call_stack_;
			StackFrame* current_frame_;
			ConstantPool constant_pool_;
			Heap heap_;
			GC gc_;
		};

	}
}
