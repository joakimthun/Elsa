#include "stack_frame.h"

namespace elsa {
	namespace vm {
				
		StackFrame::StackFrame()
		{

		}

		StackFrame::~StackFrame()
		{

		}

		void StackFrame::push(Object o)
		{
			eval_stack_.push_back(o);
		}

		Object StackFrame::pop()
		{
			auto o = eval_stack_.back();
			eval_stack_.pop_back();

			return o;
		}

		Object StackFrame::local(std::size_t i)
		{
			return locals_[i];
		}

	}
}