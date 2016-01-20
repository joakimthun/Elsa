#pragma once

#include <cstddef>
#include <vector>
#include <iostream>

#include "stack_frame.h"
#include "exceptions\runtime_exception.h"

namespace elsa {
	namespace vm {

		class CallStack {
		public:
			CallStack();
			~CallStack();

			void push(StackFrame* frame);
			StackFrame* pop();
			std::size_t size();
			StackFrame* current();
			void dump_stack_trace();

		private:
			std::vector<StackFrame*> stack_;
		};

	}
}
