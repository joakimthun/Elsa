#include "array_declaration_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<Expression> ArrayDeclarationParser::parse(ElsaParser* parser)
		{
			return std::make_unique<ArrayDeclarationExpression>(new ElsaType(ObjectType::Int));
		}

	}
}
