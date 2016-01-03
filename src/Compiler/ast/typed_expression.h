#pragma once

#include <string>

namespace elsa {
	namespace compiler {

		class ElsaType;

		class TypedExpression
		{
		public:
			virtual ~TypedExpression() {};
			virtual const std::wstring& get_name() const = 0;
			virtual const ElsaType* get_type() const = 0;
		};

	}
}

