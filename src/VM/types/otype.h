#pragma once

namespace elsa {
	namespace vm {

		enum OType : int
		{
			Undefined,
			Null,
			Int,
			Float,
			Char,
			Bool,
			GCOPtr,
		};

	}
}