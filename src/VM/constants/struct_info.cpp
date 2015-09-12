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
			return sizeof(int);
		}

		void StructInfo::add_field(FieldInfo field)
		{
			update_size(field);
			fields_.push_back(field);
		}

		void StructInfo::update_size(const FieldInfo & field)
		{
			switch (field.type)
			{
				case Int:
					size_ += sizeof(int);
					break;
				case Float:
					size_ += sizeof(float);
					break;
				case Char:
					size_ += sizeof(wchar_t);
					break;
				case Bool:
					size_ += sizeof(bool);
					break;
				//case GCOPtr:
				//	size_ += sizeof(int*);
				//	break;
				default:
					throw new ElsaException("Invalid field type.");
			}
		}
	}
}