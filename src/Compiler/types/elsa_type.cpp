#include "elsa_type.h"

namespace elsa {
	namespace compiler {

		ElsaType::ElsaType(OType type)
			:
			type_(type)
		{}

		ElsaType::ElsaType(OType type, StructInfo* si)
			:
			type_(type),
			struct_info_(si)
		{}

		OType ElsaType::get_type() const
		{
			return type_;
		}

		const StructInfo* ElsaType::get_struct_info() const
		{
			return struct_info_;
		}
	}
}
