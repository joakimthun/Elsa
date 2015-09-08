#pragma once

#include <cstddef>
#include <vector>

#include "stack_frame.h"

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
		private:
			std::vector<StackFrame*> stack_;
		};

	}
}
