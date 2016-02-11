#include "struct_factory.h"

#include "util\string_util.h"
#include "../parsing/elsa_parser.h"

namespace elsa {
	namespace compiler {

		std::unique_ptr<StructDeclarationExpression> StructFactory::create(ElsaParser* parser)
		{
			auto struct_exp = std::make_unique<StructDeclarationExpression>();

			auto name = StringUtil::create_random_string(20);
			struct_exp->set_name(name);
			parser->struct_table().add_struct(name, struct_exp.get());
			struct_exp->set_type(parser->type_checker().get_expression_type(struct_exp.get()));

			return struct_exp;
		}

	}
}

