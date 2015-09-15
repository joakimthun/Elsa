#include "call_stack.h"

namespace elsa {
	namespace vm {

		CallStack::CallStack() 
		{
		}

		CallStack::~CallStack()
		{
		}

		void CallStack::push(StackFrame* frame)
		{
			stack_.push_back(frame);
		}

		StackFrame* CallStack::pop()
		{
			if (stack_.size() == 0)
				throw RuntimeException("Can not call pop on an empty call stack.");

			auto last = stack_.back();
			stack_.pop_back();

			return last;
		}

		std::size_t CallStack::size()
		{
			return stack_.size();
		}

		StackFrame* CallStack::current()
		{
			return stack_.back();
		}
	}
}
