#include "type_converter.h"

#include "../ast/integer_literal_expression.h"
#include "../ast/byte_literal_expression.h"
#include "../ast/float_literal_expression.h"

namespace elsa {
	namespace compiler {
		
		bool TypeConverter::try_convert(std::unique_ptr<Expression>& expression, const ElsaType* target, TypeChecker* type_checker)
		{
			auto current = std::unique_ptr<ElsaType>(type_checker->get_expression_type(expression.get()));

			if (type_checker->is_of_type<IntegerLiteralExpression>(expression.get()))
			{
				auto int_value = static_cast<IntegerLiteralExpression*>(expression.get())->get_value();
				switch (target->get_type())
				{
				case ObjectType::Byte: {
					expression.reset(new ByteLiteralExpression(static_cast<uint8_t>(int_value)));
					return true;
				}
				case ObjectType::Float: {
					expression.reset(new FloatLiteralExpression(static_cast<float>(int_value)));
					return true;
				}
				default:
					break;
				}
			}

			return false;
		}
}
}
