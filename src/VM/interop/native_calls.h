#pragma once

#include <vector>
#include <cstddef>
#include <functional>
#include <iostream>

#include "../stack_frame.h"
#include "object_types\otype.h"

namespace elsa {
	namespace vm {

		class NativeCalls
		{
		public:
			NativeCalls();
			
			void invoke(std::size_t index, StackFrame* frame);

		private:
			void initialize();
			static void print(StackFrame* frame);
			static void print_ln(StackFrame* frame);
			static void print_internal(StackFrame* frame);

			std::vector<std::function<void(StackFrame*)>> functions_;
		};

	}
}