#pragma once

#include <string>
#include <sstream>
#include "vm_program.h"

namespace elsa {

	class ToString
	{
	public:
		ToString(VMProgram* program);
		~ToString() {}

		std::wstring run();
	private:
		void cycle();
		void next_opcode();
		int get_instruction(std::size_t pc);
		std::wstring vm_type_to_string(VMType type);

		VMProgram* program_;
		std::size_t pc_;
		std::size_t code_length_;
		std::wstringstream out_;
		OpCode oc_;
	};

}