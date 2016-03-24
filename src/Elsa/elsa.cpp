#include <Windows.h>
#include <memory>
#include <iostream>

#include "compiler.h"
#include "vm.h"
#include "exceptions\elsa_exception.h"
#include "exceptions\runtime_exception.h"
#include "output\to_string.h"

using namespace elsa;

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 2)
		{
			throw ElsaException("No source file specified");
		}

		auto vm_program = compiler::Compiler::compile(argv[1]);
		
		//auto ts = std::make_unique<ToString>(vm_program.get());
		//
		//std::wcout << ts->run();

		auto vm = vm::VM(*vm_program);
		vm.execute();
	}
	catch (ElsaException& e)
	{
		std::cout << e.what() << std::endl;
	}
}

