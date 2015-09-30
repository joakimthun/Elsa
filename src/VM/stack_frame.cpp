#include "stack_frame.h"

namespace elsa {
	namespace vm {
				
		StackFrame::StackFrame(const FunctionInfo* function, std::size_t ret_addr, StackFrame* parent)
			:
			function_(function),
			ret_addr_(ret_addr),
			parent_(parent)
		{
			locals_size_ = function->get_num_locals() + function->get_num_args();
			locals_ = new Object[locals_size_];
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
			if(eval_stack_.size() == 0)
				throw RuntimeException("Can not call pop on an empty evaluation stack.");

			auto o = eval_stack_.back();
			eval_stack_.pop_back();

			return o;
		}

		Object StackFrame::dump_top() const
		{
			if (eval_stack_.size() == 0)
				throw RuntimeException("Can not call pop on an empty evaluation stack.");

			return eval_stack_.back();
		}

		bool StackFrame::has_stack_entries() const
		{
			return !eval_stack_.empty();
		}

		Object StackFrame::load_local(std::size_t i) const
		{
			auto li = function_->get_num_args() + i;
			if (li > locals_size_ - 1)
				throw RuntimeException("Tried to access an out of range local.");

			return locals_[li];
		}

		Object StackFrame::load_arg(std::size_t i) const
		{
			if (i > locals_size_ - 1)
				throw RuntimeException("Tried to access an out of range argument.");

			return locals_[i];
		}

		void StackFrame::store_local(std::size_t i, Object local)
		{
			auto li = function_->get_num_args() + i;
			if (li > locals_size_ - 1)
				throw RuntimeException("Tried to store an out of range local.");

			locals_[li] = local;
		}

		void StackFrame::store_arg(std::size_t i, Object arg)
		{
			if (i > locals_size_ - 1)
				throw RuntimeException("Tried to store an out of range argument.");

			locals_[i] = arg;
		}

		std::size_t StackFrame::get_ret_addr() const
		{
			return ret_addr_;
		}

		StackFrame* StackFrame::get_parent() const
		{
			return parent_;
		}
	}
}