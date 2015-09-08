#include <iostream>

#include "vm.h"
#include "opcodes.h"

int main()
{
	using namespace elsa::vm;

	int p[]
	{
		iconst, 2,
		iconst, 6,
		imul,
		halt
	};

	auto vm = VM(p, 6);
	vm.execute();

	return 0;
}

