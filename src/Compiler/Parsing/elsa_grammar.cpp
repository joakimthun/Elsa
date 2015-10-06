#include "elsa_grammar.h"

namespace elsa {
	namespace compiler {

		ElsaGrammar::ElsaGrammar() 
		{
			initialize_grammar();
		}

		Parser* ElsaGrammar::get_parser(TokenType type)
		{
			auto it = parsers_.find(type);
			if (it != parsers_.end())
			{
				return it->second.get();
			}

			return nullptr;
		}

		void ElsaGrammar::register_prefix_op(TokenType type)
		{
			parsers_.insert(std::pair<TokenType, std::unique_ptr<Parser>>(type, std::unique_ptr<Parser>(new PrefixOperatorParser())));
		}

		void ElsaGrammar::initialize_grammar()
		{
			register_prefix_op(TokenType::Exclamation);
		}

	}
}
