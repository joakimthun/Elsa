#pragma once

#include <string>

#include "object_types\otype.h"
#include "constants\struct_info.h"

namespace elsa {
	namespace compiler {

		class ElsaType
		{
		public:
			ElsaType(OType type);
			ElsaType(OType type, StructInfo* si);

			OType get_type() const;
			const StructInfo* get_struct_info() const;
		private:
			OType type_;
			StructInfo* struct_info_;
		};

	}
}
