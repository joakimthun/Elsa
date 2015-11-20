#pragma once

#include <cstddef>
#include "object_types\vm_type.h"

namespace elsa {
	namespace vm {

		struct ArrayInfo
		{
			ArrayInfo(elsa::VMType t, std::size_t ne, std::size_t es) : type(t), num_elements(ne), element_size(es) {};
			elsa::VMType type;
			std::size_t num_elements;
			std::size_t element_size;
		};

	}
}
