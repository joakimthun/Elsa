#pragma once

#include <cstddef>
#include <vector>

#include "object.h"

namespace elsa {
	namespace vm {

		class StackFrame {
		public:
			StackFrame();
			~StackFrame();

			void push(Object o);
			Object pop();
			Object local(std::size_t i);
		private:
			std::vector<Object> eval_stack_;
			std::vector<Object> locals_;
		};

	}
}
