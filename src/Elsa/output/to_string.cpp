#include "to_string.h"

namespace elsa {

	ToString::ToString(VMProgram* program)
		:
		program_(program),
		code_length_(0),
		pc_(0)
	{
		code_length_ = program_->get_instructions().size();

		if (code_length_ == 0)
			throw RuntimeException("No program to execute.");

		if (program_->get_entry_point() < 0)
			throw RuntimeException("No entry point specified.");

		pc_ = static_cast<std::size_t>(program_->get_entry_point());
	}

	std::wstring ToString::run()
	{
		while (pc_ < code_length_)
		{
			cycle();
		}

		return out_.str();
	}

	void ToString::cycle()
	{
		out_ << get_instruction(pc_) << ": ";
		next_opcode();

		switch (oc_)
		{
		case iconst: {
			auto v = get_instruction(pc_++);
			out_ << "iconst " << v << std::endl;
			break;
		}
		case iadd: {
			out_ << "iadd" << std::endl;
			break;
		}
		case imul: {
			out_ << "imul" << std::endl;
			break;
		}
		case isub: {
			out_ << "isub" << std::endl;
			break;
		}
		case idiv: {
			out_ << "idiv" << std::endl;
			break;
		}
		case ieq: {
			out_ << "ieq" << std::endl;
			break;
		}
		case ineq: {
			out_ << "ineq" << std::endl;
			break;
		}
		case ilt: {
			out_ << "ilt" << std::endl;
			break;
		}
		case igt: {
			out_ << "igt" << std::endl;
			break;
		}
		case imod: {
			out_ << "imod" << std::endl;
			break;
		}
		case bconst: {
			auto v = get_instruction(pc_++);
			out_ << "bconst " << v << std::endl;
			break;
		}
		case badd: {
			out_ << "badd" << std::endl;
			break;
		}
		case bmul: {
			out_ << "bmul" << std::endl;
			break;
		}
		case bsub: {
			out_ << "bsub" << std::endl;
			break;
		}
		case bdiv: {
			out_ << "bdiv" << std::endl;
			break;
		}
		case beq: {
			out_ << "beq" << std::endl;
			break;
		}
		case bneq: {
			out_ << "bneq" << std::endl;
			break;
		}
		case blt: {
			out_ << "blt" << std::endl;
			break;
		}
		case bgt: {
			out_ << "bgt" << std::endl;
			break;
		}
		case bmod: {
			out_ << "bmod" << std::endl;
			break;
		}
		case fconst: {
			auto index = get_instruction(pc_++);
			auto f = program_->get_float(index);
			out_ << "fconst " << f->get_value() << std::endl;
			break;
		}
		case fadd: {
			out_ << "fadd" << std::endl;
			break;
		}
		case fmul: {
			out_ << "fmul" << std::endl;
			break;
		}
		case fsub: {
			out_ << "fsub" << std::endl;
			break;
		}
		case fdiv: {
			out_ << "fdiv" << std::endl;
			break;
		}
		case feq: {
			out_ << "feq" << std::endl;
			break;
		}
		case fneq: {
			out_ << "fneq" << std::endl;
			break;
		}
		case flt: {
			out_ << "flt" << std::endl;
			break;
		}
		case fgt: {
			out_ << "fgt" << std::endl;
			break;
		}
		case cconst: {
			auto index = get_instruction(pc_++);
			auto c = program_->get_char_at(index);
			out_ << "cconst " << c->get_value() << std::endl;
			break;
		}
		case ceq: {
			out_ << "ceq" << std::endl;
			break;
		}
		case cneq: {
			out_ << "cneq" << std::endl;
			break;
		}
		case sconst: {
			auto str_literal_index = get_instruction(pc_++);
			auto str = program_->get_string(str_literal_index)->get_value();
			out_ << "sconst " << str << std::endl;
			break;
		}
		case t_cast: {
			auto dest_type = static_cast<VMType>(get_instruction(pc_++));
			out_ << "t_cast to " << vm_type_to_string(dest_type) << std::endl;
			break;
		}
		case null: {
			out_ << "null" << std::endl;
			break;
		}
		case br: {
			auto jmp_addr = get_instruction(pc_++);
			out_ << "br " << jmp_addr << std::endl;
			break;
		}
		case br_ieq: {
			auto jmp_addr = get_instruction(pc_++);
			out_ << "br_ieq " << jmp_addr << std::endl;
			break;
		}
		case br_ineq: {
			auto jmp_addr = get_instruction(pc_++);
			out_ << "br_ineq " << jmp_addr << std::endl;
			break;
		}
		case br_feq: {
			auto jmp_addr = get_instruction(pc_++);
			out_ << "br_feq " << jmp_addr << std::endl;
			break;
		}
		case br_fneq: {
			auto jmp_addr = get_instruction(pc_++);
			out_ << "br_nfeq " << jmp_addr << std::endl;
			break;
		}
		case br_ceq: {
			auto jmp_addr = get_instruction(pc_++);
			out_ << "br_ceq " << jmp_addr << std::endl;
			break;
		}
		case br_cneq: {
			auto jmp_addr = get_instruction(pc_++);
			out_ << "br_cneq " << jmp_addr << std::endl;
			break;
		}
		case br_beq: {
			auto jmp_addr = get_instruction(pc_++);
			out_ << "br_beq " << jmp_addr << std::endl;
			break;
		}
		case br_bneq: {
			auto jmp_addr = get_instruction(pc_++);
			out_ << "br_bneq " << jmp_addr << std::endl;
			break;
		}
		case call: {
			auto addr = get_instruction(pc_);
			auto f = program_->get_func(addr);
			out_ << "call " << f->get_name() << std::endl;
			break;
		}
		case ret: {
			out_ << "ret" << std::endl;
			break;
		}
		case scall: {
			out_ << "scall" << std::endl;
			break;
		}
		case fnconst: {
			auto addr = get_instruction(pc_++);
			auto f = program_->get_func(addr);
			out_ << "fnconst " << f->get_name() << std::endl;
			break;
		}
		case l_arg: {
			auto a_index = get_instruction(pc_++);
			out_ << "l_arg " << a_index << std::endl;
			break;
		}
		case l_local: {
			auto l_index = get_instruction(pc_++);
			out_ << "l_local " << l_index << std::endl;
			break;
		}
		case s_local: {
			auto l_index = get_instruction(pc_++);
			out_ << "s_local " << l_index << std::endl;
			break;
		}
		case ncall: {
			auto index = static_cast<std::size_t>(get_instruction(pc_++));
			out_ << "ncall " << index << std::endl;
			break;
		}
		case new_struct: {
			auto i = get_instruction(pc_++);
			auto si = program_->get_struct(i);
			out_ << "new_struct " << si->get_name() << std::endl;
			break;
		}
		case l_field: {
			auto fi = get_instruction(pc_++);
			out_ << "l_field " << fi << std::endl;
			break;
		}
		case s_field: {
			auto fi = get_instruction(pc_++);
			out_ << "s_field " << fi << std::endl;
			break;
		}
		case new_arr: {
			auto type = static_cast<VMType>(get_instruction(pc_++));
			out_ << "new_arr " << vm_type_to_string(type) << std::endl;
			break;
		}
		case len_arr: {
			out_ << "len_arr" << std::endl;
			break;
		}
		case c_arr: {
			out_ << "c_arr" << std::endl;
			break;
		}
		case l_ele: {
			out_ << "l_ele" << std::endl;
			break;
		}
		case s_ele: {
			out_ << "s_ele" << std::endl;
			break;
		}
		case a_ele: {
			out_ << "a_ele" << std::endl;
			break;
		}
		case p_ele: {
			out_ << "p_ele" << std::endl;
			break;
		}
		case r_ele: {
			auto ei = get_instruction(pc_++);
			out_ << "r_ele " << ei << std::endl;
			break;
		}
		case iand: {
			out_ << "iand" << std::endl;
			break;
		}
		case ior: {
			out_ << "ior" << std::endl;
			break;
		}
		case isl: {
			out_ << "isl" << std::endl;
			break;
		}
		case isr: {
			out_ << "isr" << std::endl;
			break;
		}
		case band: {
			out_ << "band" << std::endl;
			break;
		}
		case bor: {
			out_ << "bor" << std::endl;
			break;
		}
		case halt: {
			out_ << "halt" << std::endl;
			break;
		}
		case pop: {
			out_ << "pop" << std::endl;
			break;
		}
		case nop: {
			out_ << "nop" << std::endl;
			break;
		}
		default:
			break;
		}
	}

	void ToString::next_opcode()
	{
		oc_ = (OpCode)get_instruction(pc_++);
	}

	int ToString::get_instruction(std::size_t pc)
	{
		return program_->get_instructions()[pc];
	}

	std::wstring ToString::vm_type_to_string(VMType type)
	{
		switch (type)
		{
		case elsa::VMType::NullPtr:
			return L"nullptr";
		case elsa::VMType::Int:
			return L"int";
		case elsa::VMType::Float:
			return L"float";
		case elsa::VMType::Char:
			return L"char";
		case elsa::VMType::GCOPtr:
			return L"ptr";
		case elsa::VMType::Function:
			return L"function";
		case elsa::VMType::Byte:
			return L"byte";
		default:
			return L"undefined vm type";
		}
	}

}
