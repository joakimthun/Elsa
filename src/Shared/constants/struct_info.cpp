#include "struct_info.h"

namespace elsa {

		StructInfo::StructInfo(const std::wstring& name)
			:
			name_(name),
			size_(0),
			index_(0)
		{}

		StructInfo::~StructInfo() {}

		std::wstring StructInfo::get_name() const
		{
			return name_;
		}

		std::size_t StructInfo::get_size() const
		{
			return size_;
		}

		FieldInfo* StructInfo::get_field(std::size_t index) const
		{
			if (index > fields_.size() - 1)
				throw RuntimeException("Field index out of range");

			return fields_[index].get();
		}

		void StructInfo::set_index(std::size_t index)
		{
			index_ = index;
		}

		std::size_t StructInfo::get_index() const
		{
			return index_;
		}

		const std::vector<std::unique_ptr<FieldInfo>>& StructInfo::get_fields() const
		{
			return fields_;
		}

		void StructInfo::add_field(std::unique_ptr<FieldInfo> field)
		{
			field->set_num_bytes_offset(size_);
			update_size(*field);
			fields_.push_back(std::move(field));
		}

		void StructInfo::update_size(const FieldInfo& field)
		{
			size_ += field.get_size();
		}
}