#include "vm.h"

namespace elsa {
	namespace vm {

		VM::VM(VMProgram& program)
			:
			program_(program),
			code_length_(0),
			pc_(0),
			oc_(nop)
		{
			code_length_ = program_.get_instructions().size();
			gc_ = GC(&heap_);

			if (code_length_ == 0)
				throw RuntimeException("No program to execute.");

			if (program_.get_entry_point() < 0)
				throw RuntimeException("No entry point specified.");

			pc_ = static_cast<std::size_t>(program_.get_entry_point());
		}

		VM::~VM()
		{
		}

		void VM::execute()
		{
			if (call_stack_.size() == 0)
			{
				push_main();
			}

			bool cont = false;

			if (oc_ == OpCode::halt)
				cont = true;

			while ((cont || oc_ != halt) && pc_ < code_length_)
			{
				cycle();
				cont = false;
			}
		}

		void VM::execute_one()
		{
			if (call_stack_.size() == 0)
				push_main();

			cycle();
		}

		void VM::skip_one()
		{
			next_opcode();
		}

		Object VM::eval_stack_top() const
		{
			return current_frame_->dump_top();
		}

		std::size_t VM::get_pc() const
		{
			return pc_;
		}

		GCResult VM::gc_collect()
		{
			return gc_.collect(call_stack_.current());
		}

		int VM::get_instruction(std::size_t pc)
		{
			return program_.get_instructions()[pc];
		}

		void VM::cycle()
		{
			current_frame_ = call_stack_.current();
			next_opcode();

			switch (oc_)
			{
			case iconst: {
				auto v = get_instruction(pc_++);
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
			case isub: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o2.i() - o1.i()));
				break;
			}
			case idiv: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o2.i() / o1.i()));
				break;
			}
			case ieq: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o1.i() == o2.i()));
				break;
			}
			case ineq: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o1.i() != o2.i()));
				break;
			}
			case fconst: { 
				auto index = get_instruction(pc_++);
				auto f = program_.get_float(index);
				current_frame_->push(Object(f->get_value()));
				break; 
			}
			case fadd: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o1.f() + o2.f()));
				break;
				break; 
			}
			case fmul: { 
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o1.f() * o2.f()));
				break; 
			}
			case fsub: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o2.f() - o1.f()));
				break; 
			}
			case fdiv: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o2.f() / o1.f()));
				break; 
			}
			case feq: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o1.f() == o2.f()));
				break;
			}
			case fneq: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o1.f() != o2.f()));
				break;
			}
			case cconst: {
				auto index = get_instruction(pc_++);
				auto c = program_.get_char_at(index);
				current_frame_->push(Object(c->get_value()));
				break;
			}
			case ceq: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o1.c() == o2.c()));
				break;
			}
			case cneq: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(Object(o1.c() != o2.c()));
				break;
			}
			case bconst: {
				auto v = get_instruction(pc_++) != 0;
				current_frame_->push(Object(v));
				break;
			}
			case beq: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(o1.b() == o2.b());
				break;
			}
			case bneq: {
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				current_frame_->push(o1.b() != o2.b());
				break;
			}
			case sconst: {
				auto index = get_instruction(pc_++);
				auto str = program_.get_string(index)->get_value();
				auto str_obj = heap_.alloc_array(OType::Char, str.length());

				for (std::wstring::size_type i = 0; i < str.size(); ++i)
				{
					heap_.store_element(str_obj, Object(str[i]), i);
				}

				current_frame_->push(str_obj);

				break;
			}
			case br_ieq: {
				auto jmp_addr = get_instruction(pc_++);
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();
				
				if (o1.i() == o2.i())
					pc_ = jmp_addr;

				break;
			}
			case br_ineq: {
				auto jmp_addr = get_instruction(pc_++);
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();

				if (o1.i() != o2.i())
					pc_ = jmp_addr;

				break;
			}
			case br_feq: {
				auto jmp_addr = get_instruction(pc_++);
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();

				if (o1.f() == o2.f())
					pc_ = jmp_addr;

				break;
			}
			case br_fneq: {
				auto jmp_addr = get_instruction(pc_++);
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();

				if (o1.f() != o2.f())
					pc_ = jmp_addr;

				break;
			}
			case br_beq: {
				auto jmp_addr = get_instruction(pc_++);
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();

				if (o1.b() == o2.b())
					pc_ = jmp_addr;

				break;
			}
			case br_bneq: {
				auto jmp_addr = get_instruction(pc_++);
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();

				if (o1.b() != o2.b())
					pc_ = jmp_addr;

				break;
			}
			case br_ceq: {
				auto jmp_addr = get_instruction(pc_++);
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();

				if (o1.c() == o2.c())
					pc_ = jmp_addr;

				break;
			}
			case br_cneq: {
				auto jmp_addr = get_instruction(pc_++);
				auto o1 = current_frame_->pop();
				auto o2 = current_frame_->pop();

				if (o1.c() != o2.c())
					pc_ = jmp_addr;

				break;
			}
			case call: {
				auto addr = get_instruction(pc_);

				auto f = program_.get_func(addr);
				auto sf = new StackFrame(f, pc_ + 1, call_stack_.current());
				call_stack_.push(sf);

				if (f->get_num_args() > 0)
				{
					for (int i = static_cast<int>(f->get_num_args()) - 1; i >= 0; --i)
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
				auto a_index = get_instruction(pc_++);
				current_frame_->push(current_frame_->load_arg(a_index));
				break;
			}
			case l_local: {
				auto l_index = get_instruction(pc_++);
				current_frame_->push(current_frame_->load_local(l_index));
				break;
			}
			case s_local: {
				auto l_index = get_instruction(pc_++);
				auto value = current_frame_->pop();
				current_frame_->store_local(l_index, value);
				break;
			}
			case print_ln: {
				print_line(current_frame_->pop());
				break;
			}
			case new_struct: {
				auto i = get_instruction(pc_++);
				auto si = program_.get_struct(i);
				current_frame_->push(heap_.alloc_struct(si));
				break;
			}
			case l_field: {
				auto fi = get_instruction(pc_++);
				auto instance = current_frame_->pop();
				current_frame_->push(heap_.load_field(instance, fi));
				break;
			}
			case s_field: {
				auto fi = get_instruction(pc_++);
				auto value = current_frame_->pop();
				auto instance = current_frame_->pop();
				heap_.store_field(instance, value, fi);
				break;
			}
			case new_arr: {
				auto type = (OType)get_instruction(pc_++);
				auto size = current_frame_->pop().i();
				current_frame_->push(heap_.alloc_array(type, size));
				break;
			}
			case res_arr: {
				auto new_size = current_frame_->pop().i();
				auto arr = current_frame_->pop();
				heap_.resize_array(arr, new_size);
				break;
			}
			case l_ele: {
				auto ei = get_instruction(pc_++);
				auto instance = current_frame_->pop();
				current_frame_->push(heap_.load_element(instance, ei));
				break;
			}
			case s_ele: {
				auto ei = get_instruction(pc_++);
				auto value = current_frame_->pop();
				auto instance = current_frame_->pop();
				heap_.store_element(instance, value, ei);
				break;
			}
			case halt: {
				break;
			}
			case pop: {
				current_frame_->pop();
				break;
			}
			case nop: {
				break;
			}
			default:
				break;
			}
		}

		void VM::push_main()
		{
			call_stack_.push(new StackFrame(program_.get_main(), program_.get_entry_point(), nullptr));
		}

		void VM::next_opcode()
		{
			oc_ = (OpCode)get_instruction(pc_++);
		}

		void VM::print_line(const Object& o)
		{
			if (o.get_type() == OType::Int)
				std::cout << o.i() << std::endl;
			else if(o.get_type() == OType::Float)
				std::cout << o.f() << std::endl;
			else if (o.get_type() == OType::Char)
				std::wcout << o.c() << std::endl;
			else if (o.get_type() == OType::Bool)
				std::cout << o.b() << std::endl;
			else
				throw RuntimeException("Unsupported type: print_ln");
		}
	}
}
