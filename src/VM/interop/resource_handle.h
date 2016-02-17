#pragma once

namespace elsa {
	namespace vm {

		enum class ResourceHandleType 
		{
			Window
		};

		class ResourceHandle
		{
		public:
			virtual ~ResourceHandle() {};
			virtual ResourceHandleType get_type() = 0;
		};
	}
}
