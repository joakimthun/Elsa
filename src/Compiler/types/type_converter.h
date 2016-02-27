#pragma once

#include <memory>
#include <memory>

#include "elsa_type.h"
#include "../exceptions\parsing_exception.h"
#include "type_checker.h"
#include "../ast/expression.h"

namespace elsa {
	namespace compiler {

		class TypeConverter
		{
		public:
			static bool try_convert(std::unique_ptr<Expression>& expression, const ElsaType* target, TypeChecker* type_checker);
		};

	}
}
