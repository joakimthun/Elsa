#include "call_stack.h"

namespace elsa {
	namespace vm {

		CallStack::CallStack() 
		{
		}

		CallStack::~CallStack()
		{
			while (stack_.size() > 0)
			{
				delete stack_.back();
				stack_.pop_back();
			}
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

		void CallStack::dump_stack_trace()
		{
			for (int i = static_cast<int>(stack_.size()) - 1; i >= 0; --i)
			{
				const auto fi = stack_[i]->get_function_info();
				std::wcout << fi->get_name() << L" at: " << fi->get_addr() << std::endl;
			}
		}
	}
}
