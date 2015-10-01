#pragma once

#include <stdlib.h>
#include <memory>

#include "exceptions/runtime_exception.h"
#include "constants/struct_info.h"
#include "../types/array_info.h"

namespace elsa {
	namespace vm {

		enum GCObjectType : int
		{
			Struct,
			Array
		};

		struct GCObject
		{
			GCObject(GCObjectType t) : marked(false), ptr(nullptr), si(nullptr), type(t), ai(nullptr), next(nullptr) {};

			~GCObject()
			{
				free(ptr);
			};

			bool marked;
			void* ptr;
			const StructInfo* si;
			std::unique_ptr<ArrayInfo> ai;
			GCObjectType type;
			GCObject* next;
		};

	}
}