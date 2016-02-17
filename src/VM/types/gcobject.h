#pragma once

#include <stdlib.h>
#include <memory>

#include "exceptions/runtime_exception.h"
#include "constants/struct_info.h"
#include "../types/array_info.h"
#include "../interop/resource_handle.h"

namespace elsa {
	namespace vm {

		enum GCObjectType : int
		{
			Struct,
			Array,
			Function,
			RHandle
		};

		struct GCObject
		{
			GCObject(GCObjectType t) : marked(false), ptr(nullptr), si(nullptr), type(t), ai(nullptr), next(nullptr), resource_handle_(nullptr) {};

			~GCObject()
			{
				if(ptr != nullptr)
					free(ptr);

				if (resource_handle_ != nullptr)
					delete resource_handle_;
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
			ResourceHandle* resource_handle_;
		};

	}
}