#include "field_info.h"

namespace elsa {

		FieldInfo::FieldInfo(const std::wstring& name, VMType type)
			:
			name_(name),
			type_(type),
			size_(0)
		{
			set_size();
		}

		void FieldInfo::set_num_bytes_offset(std::size_t offset)
		{
			num_bytes_offset_ = offset;
		}

		std::wstring FieldInfo::get_name() const
		{
			return name_;
		}

		VMType FieldInfo::get_type() const
		{
			return type_;
		}

		std::size_t FieldInfo::get_size() const
		{
			return size_;
		}

		std::size_t FieldInfo::get_num_bytes_offset() const
		{
			return num_bytes_offset_;
		}

		void FieldInfo::set_size()
		{
			switch (type_)
			{
			case VMType::Int:
				size_ = sizeof(int);
				break;
			case VMType::Float:
				size_ = sizeof(float);
				break;
			case VMType::Char:
				size_ = sizeof(wchar_t);
				break;
			case VMType::GCOPtr:
				size_ = sizeof(GCObject*);
				break;
			case VMType::Byte:
				size_ = sizeof(uint8_t);
				break;
			default:
				throw ElsaException("Invalid field type.");
			}
		}
}

