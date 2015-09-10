#include "stack_frame.h"

namespace elsa {
	namespace vm {
				
		StackFrame::StackFrame(FunctionEntry* function, std::size_t ret_addr)
			:
			function_(function),
			ret_addr_(ret_addr)
		{
			locals_ = new Object[function->get_num_locals() + function->get_num_args()];
		}

		StackFrame::~StackFrame() 
		{
			delete[] locals_;
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

		bool StackFrame::has_stack_entries() const
		{
			return !eval_stack_.empty();
		}

		Object StackFrame::get_local(std::size_t i) const
		{
			// TODO: Add custom exceptions
			if (i > function_->get_num_locals() - 1)
				throw;

			return locals_[i];
		}

		void StackFrame::add_local(std::size_t i, Object local)
		{
			locals_[i] = local;
		}

		std::size_t StackFrame::get_ret_addr() const
		{
			return ret_addr_;
		}

	}
}