#include "vm.h"

namespace elsa {
	namespace vm {

		VM::VM(int* code, std::size_t length)
			:
			code_(code),
			code_length_(length),
			pc_(0),
			entry_point_(-1),
			oc_(nop)
		{
		}

		VM::~VM()
		{
		}

		void VM::execute()
		{
			if (entry_point_ == -1)
				throw;

			// Push main on the call stack
			call_stack_.push(new StackFrame(constant_pool_.get_func_at(entry_point_), entry_point_));

			while (oc_ != halt && pc_ < code_length_)
			{
				current_frame_ = call_stack_.current();

				cycle();
			}

			delete call_stack_.pop();
		}

		void VM::add_constant_entry(ConstantEntry* entry)
		{
			constant_pool_.add_entry(entry);
		}

		void VM::set_entry_point(std::size_t entry_point)
		{
			entry_point_ = entry_point;
			pc_ = entry_point_;
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
			case call_static: {
				auto addr = code_[pc_];

				// TODO: Copy args from callers stack
				auto func = constant_pool_.get_func_at(addr);
				auto sf = new StackFrame(func, pc_ + 1);
				call_stack_.push(sf);

				if (func->get_num_args() > 0)
				{
					for (std::size_t i = func->get_num_args(); i >= 0; --i)
					{
						sf->add_local(i, current_frame_->pop());
					}
				}

				pc_ = addr;
				break;
			}
			case ret: {
				std::unique_ptr<StackFrame> sf(call_stack_.pop());
				// TODO: Push the return value on the stack (if there is one)
				pc_ = sf.get()->get_ret_addr();
				break;
			}
			case print_ln: {
				print_line(current_frame_->pop());
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

		void VM::print_line(const Object& o)
		{
			if (o.get_type() == OType::Int)
				std::cout << o.i() << std::endl;
			else if(o.get_type() == OType::Float)
				std::cout << o.f() << std::endl;
			else if (o.get_type() == OType::Char)
				std::cout << o.c() << std::endl;
		}
	}
}
