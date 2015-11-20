#pragma once

namespace elsa {
	namespace compiler {

		enum Precedence : int
		{
			Assignment = 1,		// =, +=, -=, /=
			ConditionalOr = 2,  // ||
			ConditionalAnd = 3, // &&
			Equality = 4,		// ==, !=
			Relational = 5,		// <, >, <=, >=
			Sum = 6,			// + , -
			Product = 7,		// * , /
		};

	}
}
