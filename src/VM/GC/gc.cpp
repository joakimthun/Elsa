#include "gc.h"

namespace elsa {
	namespace vm {

		GC::GC() 
			:
			num_marked_(0),
			num_swept_(0)
		{}

		GCResult GC::collect(StackFrame* top_frame, Heap& heap)
		{
			markAll(top_frame);
			sweep(heap);

			return GCResult();
		}

		void GC::markAll(StackFrame* top_frame)
		{
			num_marked_ = 0;

			auto current_frame = top_frame;
			while (current_frame != nullptr)
			{
				for (std::size_t li = 0; li < current_frame->locals_size_; ++li)
				{
					mark(current_frame->locals_[li]);
				}

				for (std::vector<Object>::size_type vi = 0; vi != current_frame->eval_stack_.size(); ++vi)
				{
					mark(current_frame->eval_stack_.at(vi));
				}

				current_frame = current_frame->get_parent();
			}
		}

		void GC::sweep(Heap& heap)
		{
			num_swept_ = 0;
		}

		void GC::mark(Object& obj)
		{
		}
	}
}

