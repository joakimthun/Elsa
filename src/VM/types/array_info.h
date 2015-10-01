#pragma once

#include <cstddef>

namespace elsa {
	namespace vm {

		enum elsa::OType;

		struct ArrayInfo
		{
			ArrayInfo(OType t, std::size_t ne, std::size_t es) : type(t), num_elements(ne), element_size(es) {};
			elsa::OType type;
			std::size_t num_elements;
			std::size_t element_size;
		};

	}
}
