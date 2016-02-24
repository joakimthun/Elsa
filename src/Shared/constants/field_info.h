#pragma once

#include <cstddef>
#include <string>
#include <stdint.h>

#include "../exceptions/elsa_exception.h"
#include "../object_types/vm_type.h"

struct GCObject;

namespace elsa {

		class FieldInfo
		{
		public:
			FieldInfo(const std::wstring& n, VMType t);

			void set_num_bytes_offset(std::size_t offset);

			std::wstring get_name() const;
			VMType get_type() const;
			std::size_t get_size() const;
			std::size_t get_num_bytes_offset() const;

		private:
			void set_size();

			std::wstring name_;
			VMType type_;
			std::size_t size_;
			std::size_t num_bytes_offset_;
		};

}
