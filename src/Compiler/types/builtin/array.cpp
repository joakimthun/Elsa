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

			// Push element
			auto push = std::make_unique<FunctionInfo>(L"Push", 2, 0, program->get_next_instruction_index(), FunctionType::Member, true);
			program->emit(OpCode::l_arg);
			program->emit(0);
			program->emit(OpCode::l_arg);
			program->emit(1);
			program->emit(OpCode::a_ele);
			program->emit(OpCode::ret);
			si->add_function(push.get());
			program->add_func(std::move(push));

			// Pop element
			auto pop = std::make_unique<FunctionInfo>(L"Pop", 1, 0, program->get_next_instruction_index(), FunctionType::Member, true);
			program->emit(OpCode::l_arg);
			program->emit(0);
			program->emit(OpCode::p_ele);
			program->emit(OpCode::ret);
			si->add_function(pop.get());
			program->add_func(std::move(pop));

			program->add_struct(std::move(si));
		}

		void Array::build_symbol(StructTable* table)
		{
			auto struct_exp = std::make_unique<StructDeclarationExpression>(true);
			struct_exp->set_name(L"Array");

			auto push = std::make_unique<FuncDeclarationExpression>();
			push->set_name(L"Push");
			push->set_num_args(1);
			push->set_num_locals(0);
			push->set_return_type(new ElsaType(ObjectType::Generic));

			auto push_arg1 = std::make_unique<ArgumentExpression>();
			push_arg1->set_name(L"arg1");
			push_arg1->set_type(new ElsaType(ObjectType::Generic));
			push->add_args_expression(std::move(push_arg1));

			struct_exp->add_member_function(std::move(push));

			auto pop = std::make_unique<FuncDeclarationExpression>();
			pop->set_name(L"Pop");
			pop->set_num_args(0);
			pop->set_num_locals(0);
			pop->set_return_type(new ElsaType(ObjectType::Generic));

			//auto pop_arg1 = std::make_unique<ArgumentExpression>();
			//pop_arg1->set_name(L"arg1");
			//pop_arg1->set_type(new ElsaType(ObjectType::Void));
			//// Add args exp, type checking?
			//pop->add_args_expression(std::move(pop_arg1));

			struct_exp->add_member_function(std::move(pop));

			table->add_struct(L"Array", struct_exp.release());
		}
	}
}
