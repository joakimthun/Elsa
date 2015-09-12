#include "struct_info.h"

namespace elsa {
	namespace vm {

		StructInfo::StructInfo(const std::string& name) 
			:
			name_(name)
		{}

		StructInfo::~StructInfo() {}

		std::string StructInfo::get_name() const
		{
			return name_;
		}

		std::size_t StructInfo::get_size() const
		{
			return sizeof(int);
		}

	}
}