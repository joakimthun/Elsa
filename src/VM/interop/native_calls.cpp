#include "native_calls.h"

namespace elsa {
	namespace vm {

		NativeCalls::NativeCalls()
		{
			initialize();
		}
		
		void NativeCalls::invoke(std::size_t index, StackFrame* frame, OType type)
		{
			functions_[index](frame, type);
		}
		
		void NativeCalls::initialize()
		{
			functions_.push_back(print);
			functions_.push_back(print_ln);
		}

		void NativeCalls::print(StackFrame* frame, OType type)
		{
			print_internal(frame, type);
		}

		void NativeCalls::print_ln(StackFrame* frame, OType type)
		{
			print_internal(frame, type);
			std::cout << std::endl;
		}

		void NativeCalls::print_internal(StackFrame * frame, OType type)
		{
			auto object = frame->pop();

			if (type == OType::Int)
				std::cout << object.i();
			else if (type == OType::Float)
				std::cout << object.f();
			else if (type == OType::Char)
				std::wcout << object.c();
			else if (type == OType::Bool)
				std::cout << object.b();
			else
				throw RuntimeException("Unsupported type: print_ln");
		}

	}
}
