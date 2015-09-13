#include "field_info.h"

namespace elsa {
	namespace vm {

		FieldInfo::FieldInfo(const std::string& name, OType type)
			:
			name_(name),
			type_(type)
		{
			set_size();
		}

		void FieldInfo::set_num_bytes_offset(std::size_t offset)
		{
			num_bytes_offset_ = offset;
		}

		std::string FieldInfo::get_name() const
		{
			return name_;
		}

		OType FieldInfo::get_type() const
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
			case Int:
				size_ = sizeof(int);
				break;
			case Float:
				size_ = sizeof(float);
				break;
			case Char:
				size_ = sizeof(wchar_t);
				break;
			case Bool:
				size_ = sizeof(bool);
				break;
				//case GCOPtr:
				//	size_ += sizeof(int*);
				//	break;
			default:
				throw ElsaException("Invalid field type.");
			}
		}
	}
}

