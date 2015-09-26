#pragma once

namespace elsa {
	namespace vm {

		class GC
		{
		public:
			GC();
			~GC();

			void mark();
			void sweep();
		};

	}
}
