#pragma once

#include <stdlib.h>
#include <memory>

#include "../exceptions/runtime_exception.h"
#include "../constants/struct_info.h"
#include "../constants/array_info.h"

namespace elsa {
	namespace vm {

		enum GCObjectType : int
		{
			Struct,
			Array
		};

		struct GCObject
		{
			inline GCObject(GCObjectType t) : marked(false), ptr(nullptr), si(nullptr), type(t), ai(nullptr) {};

			inline ~GCObject()
			{
				free(ptr);
			};

			bool marked;
			void* ptr;
			StructInfo* si;
			std::unique_ptr<ArrayInfo> ai;
			GCObjectType type;
		};

	}
}