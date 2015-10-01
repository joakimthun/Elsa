#pragma once

#include <cstddef>
#include <string>

#include "../exceptions/elsa_exception.h"
#include "..\object_types\otype.h"

struct GCObject;

namespace elsa {

		class FieldInfo
		{
		public:
			FieldInfo(const std::string& n, OType t);

			void set_num_bytes_offset(std::size_t offset);

			std::string get_name() const;
			OType get_type() const;
			std::size_t get_size() const;
			std::size_t get_num_bytes_offset() const;

		private:
			void set_size();

			std::string name_;
			OType type_;
			std::size_t size_;
			std::size_t num_bytes_offset_;
		};

}
