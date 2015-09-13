#pragma once

#include <stdlib.h>

#include "../exceptions/runtime_exception.h"
#include "../constants/struct_info.h"

namespace elsa {
	namespace vm {

		struct GCObject
		{
			inline GCObject() : marked(false), ptr(nullptr), si(nullptr) {};

			inline ~GCObject()
			{
				free(ptr);
			};

			bool marked;
			void* ptr;
			StructInfo* si;
		};

	}
}