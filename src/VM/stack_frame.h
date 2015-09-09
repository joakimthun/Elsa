#pragma once

#include <cstddef>
#include <vector>

#include "object.h"
#include "constants\function_entry.h"

namespace elsa {
	namespace vm {

		class StackFrame {
		public:
			StackFrame(FunctionEntry* function, std::size_t ret_addr);
			~StackFrame();

			void push(Object o);
			Object pop();
			Object get_local(std::size_t i);
			void add_local(std::size_t i, Object local);
			std::size_t get_ret_addr();

		private:
			std::vector<Object> eval_stack_;
			Object* locals_;
			std::size_t ret_addr_;
			FunctionEntry* function_;
		};

	}
}
