#include <memory>
#include <iostream>

#include "compiler.h"
#include "vm.h"
#include "exceptions\elsa_exception.h"

using namespace elsa;

int main(int argc, char* argv[])
{
	try
	{
		auto vm_program = compiler::Compiler::compile("programs\\program1.elsa");
		auto vm = vm::VM(*vm_program);
		vm.execute();
	}
	catch (ElsaException& e)
	{
		std::cout << e.what() << std::endl;
	}
}

