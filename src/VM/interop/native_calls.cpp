#include "native_calls.h"

namespace elsa {
	namespace vm {

		NativeCalls::NativeCalls()
		{
			initialize();
		}
		
		void NativeCalls::invoke(std::size_t index, StackFrame* frame)
		{
			functions_[index](frame);
		}
		
		void NativeCalls::initialize()
		{
			functions_.push_back(print);
			functions_.push_back(print_ln);
		}

		void NativeCalls::print(StackFrame* frame)
		{
			print_internal(frame);
		}

		void NativeCalls::print_ln(StackFrame* frame)
		{
			print_internal(frame);
			std::cout << std::endl;
		}

		void NativeCalls::print_internal(StackFrame * frame)
		{
			auto object = frame->pop();

			if (object.get_type() == elsa::VMType::Int)
				std::cout << object.i();
			else if (object.get_type() == elsa::VMType::Float)
				std::cout << object.f();
			else if (object.get_type() == elsa::VMType::Char)
				std::wcout << object.c();
			else
				throw RuntimeException("Unsupported type: print_ln");
		}

	}
}
