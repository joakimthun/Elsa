#include "vm.h"

namespace elsa {
	namespace vm {

		VM::VM()
			:
			code_length_(0),
			pc_(0),
			entry_point_(-1),
			oc_(nop)
		{
		}

		VM::VM(const std::vector<int>& code)
			:
			code_(code),
			code_length_(code.size()),
			pc_(0),
			entry_point_(-1),
			oc_(nop)
		{
			code_length_ = code_.size();
		}

		VM::~VM()
		{
		}

		void VM::execute()
		{
			try 
			{
				if (code_length_ == 0)
					throw RuntimeException("No program to execute.");

				if (entry_point_ == -1)
					throw RuntimeException("No entry point specified.");

				// Push main on the call stack
				call_stack_.push(new StackFrame(constant_pool_.get_func_at(entry_point_), entry_point_));

				while (oc_ != halt && pc_ < code_length_)
				{
					current_frame_ = call_stack_.current();

					cycle();
				}

				delete call_stack_.pop();
			}
			catch (ElsaException& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		void VM::set_program(const std::vector<int>& code)
		{
			code_ = code;
			code_length_ = code.size();
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
			case isub: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o2.i() - o1.i()));
				break;
			}
			case imul: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o1.i() * o2.i()));
				break;
			}
			case b_ieq: {
				auto jmp_addr = code_[pc_++];
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				
				if (o1.i() == o2.i())
					pc_ = jmp_addr;

				break;
			}
			case b_ineq: {
				auto jmp_addr = code_[pc_++];
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();

				if (o1.i() != o2.i())
					pc_ = jmp_addr;

				break;
			}
			case call_static: {
				auto addr = code_[pc_];

				auto f = constant_pool_.get_func_at(addr);
				auto sf = new StackFrame(f, pc_ + 1);
				call_stack_.push(sf);

				if (f->get_num_args() > 0)
				{
					for (int i = f->get_num_args() - 1; i >= 0; --i)
					{
						sf->store_arg(i, current_frame_->pop());
					}
				}

				pc_ = addr;
				break;
			}
			case ret: {
				{
					std::unique_ptr<StackFrame> sf(call_stack_.pop());
					auto ret_addr = sf.get()->get_ret_addr();

					// Push the return value on the stack (if there is one)
					// Add support for multiple return values?
					if (sf.get()->has_stack_entries())
					{
						call_stack_.current()->push(sf.get()->pop());
					}

					pc_ = ret_addr;
				}
				break;
			}
			case l_arg: {
				auto a_index = code_[pc_++];
				current_frame_->push(current_frame_->load_arg(a_index));
				break;
			}
			case l_local: {
				auto l_index = code_[pc_++];
				current_frame_->push(current_frame_->load_local(l_index));
				break;
			}
			case s_local: {
				auto l_index = code_[pc_++];
				auto value = current_frame_->pop();
				current_frame_->store_local(l_index, value);
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
