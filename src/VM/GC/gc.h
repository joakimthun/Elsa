#pragma once

#include <cstddef>

#include "../memory/heap.h"
#include "../stack_frame.h"

namespace elsa {
	namespace vm {

		struct GCResult
		{
			std::size_t num_marked;
			std::size_t num_swept;
		};

		class GC
		{
		public:
			GC();

			GCResult collect(StackFrame* top_frame, Heap& heap);
		private:
			void markAll(StackFrame* top_frame);
			void sweep(Heap& heap);
			void mark(Object& obj);

			std::size_t num_marked_;
			std::size_t num_swept_;
		};

	}
}
