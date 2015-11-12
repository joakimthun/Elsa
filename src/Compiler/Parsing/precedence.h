#pragma once

namespace elsa {
	namespace compiler {

		enum Precedence : int
		{
			Assignment = 1,		// =
			Sum = 2,			// + , -
			Product = 3,		// * , /
		};

	}
}
