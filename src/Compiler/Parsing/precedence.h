#pragma once

namespace elsa {
	namespace compiler {

		enum Precedence : int
		{
			Assignment = 1,		// =
			ConditionalAnd = 2, // &&
			ConditionalOr = 3,  // ||
			Sum = 4,			// + , -
			Product = 5,		// * , /
		};

	}
}
