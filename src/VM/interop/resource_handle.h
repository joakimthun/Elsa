#pragma once

namespace elsa {
	namespace vm {

		enum class ResourceHandleType 
		{
			Window,
			File
		};

		class ResourceHandle
		{
		public:
			virtual ~ResourceHandle() {};
			virtual ResourceHandleType get_type() = 0;
		};
	}
}
