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
			Object alloc_array(OType type, std::size_t size);
			void realloc_array(Object& instance, std::size_t new_size);
			void dealloc(Object& o);

			Object load_field(const Object& instance, FieldInfo* fi);
			Object load_field(const Object& instance, std::size_t field_index);
			void store_field(const Object& instance, const Object& value, FieldInfo* fi);
			void store_field(const Object& instance, const Object& value, std::size_t field_index);
			Object load_element(const Object& instance, std::size_t element_index);
			void store_element(const Object& instance, const Object& value, std::size_t element_index);

		private:
			void assert_is_struct(const Object& instance);
			void assert_is_array(const Object& instance);
			void assert_array_index_in_range(const Object& instance, std::size_t element_index);
			byte* get_field_ptr(void* s_ptr, FieldInfo* f);
			std::size_t get_size_of_type(OType type);
			void init_struct(const Object& instance);
		};

	}
}