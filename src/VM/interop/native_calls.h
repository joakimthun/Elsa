#pragma once

#include <string>
#include <string.h>
#include <vector>
#include <cstddef>
#include <functional>
#include <iostream>

#include "../stack_frame.h"
#include "object_types/vm_type.h"

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
			static void are_eq(StackFrame* frame);
			static bool are_eq_internal(StackFrame* frame);
			static void assert_eq(StackFrame* frame);
			static void ref_eq(StackFrame* frame);
			static bool ref_eq_internal(const Object& first, const Object& second);

			std::vector<std::function<void(StackFrame*)>> functions_;
		};

	}
}