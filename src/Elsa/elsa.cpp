#include <memory>

#include "compiler.h"
#include "vm.h"

using namespace elsa;

int main(int argc, char* argv[])
{
	auto vm_program = compiler::Compiler::compile("programs\\program1.elsa");
	auto vm = vm::VM(*vm_program);

	vm.execute();
}

