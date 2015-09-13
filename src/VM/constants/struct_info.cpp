#include "struct_info.h"

namespace elsa {
	namespace vm {

		StructInfo::StructInfo(const std::string& name) 
			:
			name_(name),
			size_(0)
		{}

		StructInfo::~StructInfo() {}

		std::string StructInfo::get_name() const
		{
			return name_;
		}

		std::size_t StructInfo::get_size() const
		{
			return size_;
		}

		void StructInfo::add_field(FieldInfo* field)
		{
			update_size(*field);
			fields_.push_back(std::unique_ptr<FieldInfo>(field));
		}

		void StructInfo::update_size(const FieldInfo & field)
		{
			size_ += field.get_size();
		}
	}
}