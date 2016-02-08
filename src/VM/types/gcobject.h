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
			Array,
			Function
		};

		struct GCObject
		{
			GCObject(GCObjectType t) : marked(false), ptr(nullptr), si(nullptr), type(t), ai(nullptr), next(nullptr) {};

			~GCObject()
			{
				free(ptr);
			};

			void swap_array(void* new_ptr, ArrayInfo* new_ai)
			{
				auto old_ptr = ptr;
				ptr = new_ptr;
				ai.reset(new_ai);
			}

			bool marked;
			void* ptr;
			int addr;
			const StructInfo* si;
			std::unique_ptr<ArrayInfo> ai;
			GCObjectType type;
			GCObject* next;
		};

	}
}