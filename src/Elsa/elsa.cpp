#include <memory>

#include "compiler.h"
#include "vm.h"

using namespace elsa;

int main(int argc, char* argv[])
{
	auto vm_program = compiler::Compiler::compile("programs\\program1.elsa");

	// Debug
	//vm_program->emit(OpCode::l_local);
	//vm_program->emit(0);
	//vm_program->emit(OpCode::print_ln);

	auto vm = vm::VM(*vm_program);

	vm.execute();
}

