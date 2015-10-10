#include "type_checker.h"

namespace elsa {
	namespace compiler {

		ElsaType* TypeChecker::get_expression_type(Expression* expression)
		{
			return nullptr;
		}

		ElsaType* TypeChecker::get_type_from_token(TokenType type)
		{
			switch (type)
			{
			case TokenType::Void: {
				return new ElsaType(OType::Void);
			}
			case TokenType::Int: {
				return new ElsaType(OType::Int);
			}
			case TokenType::Float: {
				return new ElsaType(OType::Float);
			}
			case TokenType::Char: {
				return new ElsaType(OType::Char);
			}
			case TokenType::Bool: {
				return new ElsaType(OType::Bool);
			}
			case TokenType::IntegerLiteral: {
				return new ElsaType(OType::Int);
			}
			case TokenType::FloatLiteral: {
				return new ElsaType(OType::Float);
			}
			case TokenType::CharLiteral: {
				return new ElsaType(OType::Char);
			}
			case TokenType::BoolLiteral: {
				return new ElsaType(OType::Bool);
			}
			default:
				throw ParsingException("Invalid type.");
			}
		}
	}
}
