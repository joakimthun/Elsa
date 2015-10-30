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
			
			void invoke(std::size_t index, StackFrame* frame, OType type);

		private:
			void initialize();
			static void print(StackFrame* frame, OType type);
			static void print_ln(StackFrame* frame, OType type);
			static void print_internal(StackFrame* frame, OType type);

			std::vector<std::function<void(StackFrame*, OType)>> functions_;
		};

	}
}