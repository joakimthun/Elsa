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
			functions_.push_back(ref_eq);
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
				return ref_eq_internal(o1, o2);
			}
			else
			{
				switch (o1.get_type())
				{
				case VMType::Int:
					return o1.i() == o2.i();
				case VMType::Float:
					return o1.f() == o2.f();
				case VMType::Char:
					return o1.c() == o2.c();
				default:
					throw RuntimeException("Equals failed, unknown type.");
				}
			}

			return true;
		}

		void NativeCalls::assert_eq(StackFrame* frame)
		{
			if (!are_eq_internal(frame))
				throw RuntimeException("AssertEq failed.");
		}

		void NativeCalls::ref_eq(StackFrame* frame)
		{
			const auto first = frame->pop();
			const auto second = frame->pop();

			if(first.get_type() != VMType::GCOPtr || second.get_type() != VMType::GCOPtr)
				throw RuntimeException("Reference equals is only supported for reference types.");

			frame->push(Object(ref_eq_internal(first, second)));
		}

		bool NativeCalls::ref_eq_internal(const Object& first, const Object& second)
		{
			if (first.gco()->type != second.gco()->type)
				return false;

			if (first.gco()->type == GCObjectType::Array)
			{
				if (first.gco()->ai->type != second.gco()->ai->type)
					return false;

				if (first.gco()->ptr != second.gco()->ptr)
					return false;
			}
			else
			{
				if (first.gco()->si->get_name() != second.gco()->si->get_name())
					return false;

				if (first.gco()->ptr != second.gco()->ptr)
					return false;
			}

			return true;
		}
	}
}
