#include "stack_frame.h"

namespace elsa {
	namespace vm {
				
		StackFrame::StackFrame(FunctionEntry* function, std::size_t ret_addr)
			:
			function_(function),
			ret_addr_(ret_addr)
		{
		}

		StackFrame::~StackFrame() {}

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
			// TODO: Add custom exceptions
			if (i > function_->get_num_locals() - 1)
				throw;

			return locals_[i];
		}

		std::size_t StackFrame::get_ret_addr()
		{
			return ret_addr_;
		}

	}
}