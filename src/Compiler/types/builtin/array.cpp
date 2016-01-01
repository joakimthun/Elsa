#include "array.h"

namespace elsa {
	namespace compiler {

		void Array::init(VMProgram* program)
		{
			build_info(program);
		}

		void Array::init(StructTable* table)
		{
			build_symbol(table);
		}

		void Array::build_info(VMProgram* program)
		{
			auto si = std::make_unique<StructInfo>(L"Array");

			// Add element
			auto add = std::make_unique<FunctionInfo>(L"Add", 2, 0, program->get_next_instruction_index(), FunctionType::Member, true);
			program->emit(OpCode::l_arg);
			program->emit(0);
			program->emit(OpCode::l_arg);
			program->emit(1);
			program->emit(OpCode::a_ele);
			si->add_function(std::move(add));

			program->add_struct(std::move(si));
		}

		void Array::build_symbol(StructTable* table)
		{
			auto struct_exp = std::make_unique<StructDeclarationExpression>();
			struct_exp->set_name(L"Array");

			auto add = std::make_unique<FuncDeclarationExpression>();
			add->set_name(L"Add");
			add->set_num_args(1);
			add->set_num_locals(0);
			add->set_return_type(new ElsaType(ObjectType::Void));

			table->add_struct(L"Array", struct_exp.release());
		}
	}
}
