#pragma once

#include <cstddef>

#include "../memory/heap.h"
#include "../stack_frame.h"
#include "exceptions/runtime_exception.h"
#include "../types/gcobject.h"

namespace elsa {
	namespace vm {

		struct GCResult
		{
			GCResult(std::size_t num_marked, std::size_t num_swept)
			{
				this->num_marked = num_marked;
				this->num_swept = num_swept;
			};

			std::size_t num_marked;
			std::size_t num_swept;
		};

		class GC
		{
		public:
			GC();
			GC(Heap* heap);

			GCResult collect(StackFrame* top_frame);
		private:
			void markAll(StackFrame* top_frame);
			void sweep();
			void mark(Object& obj);
			void mark_struct(Object& obj);
			void mark_array(Object& obj);

			std::size_t num_marked_;
			std::size_t num_swept_;
			Heap* heap_;
		};

	}
}
