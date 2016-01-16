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
			functions_.push_back(are_eq);
			functions_.push_back(assert_eq);
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

		void NativeCalls::print_internal(StackFrame* frame)
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

		void NativeCalls::are_eq(StackFrame* frame)
		{
			frame->push(Object(are_eq_internal(frame)));
		}

		bool NativeCalls::are_eq_internal(StackFrame* frame)
		{
			const auto o1 = frame->pop();
			const auto o2 = frame->pop();

			if (o1.get_type() != o2.get_type())
				return false;

			if (o1.get_type() == VMType::GCOPtr)
			{
				if (o1.gco()->type != o2.gco()->type)
					return false;

				if (o1.gco()->type == GCObjectType::Array)
				{
					if (o1.gco()->ai->type != o2.gco()->ai->type)
						return false;

					if (o1.gco()->ptr != o2.gco()->ptr)
						return false;
				}
				else
				{
					if (o1.gco()->si->get_name() != o2.gco()->si->get_name())
						return false;

					if (o1.gco()->ptr != o2.gco()->ptr)
						return false;
				}
			}
			else
			{
				if (memcmp(&o1.get_value(), &o2.get_value(), sizeof(Value)) != 0)
					return false;
			}

			return true;
		}

		void NativeCalls::assert_eq(StackFrame* frame)
		{
			if (!are_eq_internal(frame))
				throw RuntimeException("AssertEq failed, objects are not of the same type.");
		}

	}
}
