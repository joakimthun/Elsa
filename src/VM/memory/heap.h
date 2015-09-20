#pragma once

#include <cstddef>
#include <cstdint>
#include <stdlib.h>
#include <vector>
#include <memory>

#include "../types/otype.h"
#include "../types/object.h"
#include "../constants/struct_info.h"
#include "../exceptions/runtime_exception.h"

namespace elsa {
	namespace vm {

		typedef int8_t byte;

		class Heap
		{
		public:
			Heap();
			~Heap();

			Object alloc_struct(StructInfo* si);
			Object alloc_array(OType type, std::size_t num_elements);
			void realloc_array(Object& instance, std::size_t new_size);
			void dealloc(Object& o);

			Object load_field(const Object& instance, std::size_t field_index);
			void store_field(const Object& instance, const Object& value, std::size_t field_index);

		private:
			void assert_is_gcoptr(const Object& instance);
			byte* get_field_ptr(void* s_ptr, FieldInfo* f);
			std::size_t get_size_of_type(OType type);
		};

	}
}