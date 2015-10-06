#include "elsa_grammar.h"

namespace elsa {
	namespace compiler {

		ElsaGrammar::ElsaGrammar() 
		{
			initialize_grammar();
		}

		PrefixParser* ElsaGrammar::get_prefix_parser(TokenType type)
		{
			auto it = prefix_parsers_.find(type);
			if (it != prefix_parsers_.end())
			{
				return it->second.get();
			}

			return nullptr;
		}

		void ElsaGrammar::register_prefix_op(TokenType type)
		{
			prefix_parsers_.insert(std::pair<TokenType, std::unique_ptr<PrefixParser>>(type, std::unique_ptr<PrefixParser>(new PrefixOperatorParser())));
		}

		void ElsaGrammar::initialize_grammar()
		{
			register_prefix_op(TokenType::Exclamation);
		}

	}
}
