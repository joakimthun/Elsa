#pragma once

#include <cstddef>
#include <cstdint>
#include <stdlib.h>
#include <vector>
#include <memory>
#include <algorithm>

#include "object_types/otype.h"
#include "../types/object.h"
#include "constants/struct_info.h"
#include "exceptions/runtime_exception.h"
#include "../types/gcobject.h"

namespace elsa {
	namespace vm {
		class GC;
		typedef int8_t byte;

		class Heap
		{
			friend class GC;
		public:
			Heap();
			~Heap();

			Object alloc_struct(const StructInfo* si);
			Object alloc_array(elsa::OType type, std::size_t size);
			void resize_array(Object& instance, std::size_t new_size);

			Object load_field(const Object& instance, FieldInfo* fi);
			Object load_field(const Object& instance, std::size_t field_index);
			void store_field(const Object& instance, const Object& value, FieldInfo* fi);
			void store_field(const Object& instance, const Object& value, std::size_t field_index);
			Object load_element(const Object& instance, std::size_t element_index);
			void store_element(const Object& instance, const Object& value, std::size_t element_index);
			std::size_t get_num_objects() const;

		private:
			void assert_is_struct(const Object& instance);
			void assert_is_array(const Object& instance);
			void assert_array_index_in_range(const Object& instance, std::size_t element_index);
			byte* get_field_ptr(void* s_ptr, FieldInfo* f);
			std::size_t get_size_of_type(elsa::OType type);
			void init_struct(const Object& instance);
			void init_array(const Object& instance);
			void copy_array(const Object& old_array, Object& new_array);
			Object get_default_value(elsa::OType type);
			void link_new_object(GCObject* obj);
			void increment_num_objects();

			std::size_t num_objects_;
			GCObject* base_;
		};

	}
}