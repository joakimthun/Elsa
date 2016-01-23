#pragma once

#include <string>
#include <string.h>
#include <vector>
#include <cstddef>
#include <functional>
#include <iostream>

#include "../stack_frame.h"
#include "object_types/vm_type.h"
#include "../memory/heap.h"

namespace elsa {
	namespace vm {

		class NativeCalls
		{
		public:
			NativeCalls();
			
			void invoke(std::size_t index, StackFrame* frame, Heap* heap);

		private:
			void initialize();
			static void print(StackFrame* frame, Heap* heap);
			static void print_ln(StackFrame* frame, Heap* heap);
			static void print_internal(StackFrame* frame, Heap* heap);
			static void are_eq(StackFrame* frame, Heap* heap);
			static bool are_eq_internal(StackFrame* frame);
			static void assert_eq(StackFrame* frame, Heap* heap);
			static void ref_eq(StackFrame* frame, Heap* heap);
			static bool ref_eq_internal(const Object& first, const Object& second);

			std::vector<std::function<void(StackFrame*, Heap*)>> functions_;
			Heap* heap_;
		};

	}
}