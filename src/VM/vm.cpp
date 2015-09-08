#include "vm.h"

namespace elsa {
	namespace vm {

		VM::VM(int* code, std::size_t length)
			:
			code_(code),
			code_length_(length),
			pc_(0),
			oc_(nop)
		{
		}

		VM::~VM()
		{
		}

		void VM::execute()
		{
			call_stack_.push(new StackFrame());

			while (oc_ != halt && pc_ < code_length_)
			{
				current_frame_ = call_stack_.current();

				cycle();
			}
		}

		void VM::cycle()
		{
			oc_ = (OpCode)code_[pc_++];

			switch (oc_)
			{
			case iconst: {
				auto v = code_[pc_++];
				current_frame_->push(Object(v));
				break;
			}
			case iadd: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o1.i() + o2.i()));
				break;
			}
			case imul: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o1.i() * o2.i()));
				break;
			}
			case print: {
				//std::cout 
				break;
			}
			case halt: {
				break;
			}
			case nop: {
				break;
			}
			default:
				break;
			}
		}
	}
}
