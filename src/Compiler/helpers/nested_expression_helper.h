#pragma once

#include <vector>

#include "../ast/variable_declaration_expression.h"
#include "../ast/func_declaration_expression.h"
#include "../ast/conditional_expression.h"
#include "../ast/loop_expression.h"
#include "../ast/return_expression.h"
#include "../ast/func_call_expression.h"

namespace elsa {
	namespace compiler {

		class NestedExpressionHelper
		{
		public:
			template<typename TExpression>
			static void get_nested_expressions(Expression* exp, std::vector<TExpression*>& expressions)
			{
				auto target_ext = dynamic_cast<TExpression*>(exp);
				if (target_ext != nullptr)
				{
					expressions.push_back(target_ext);
				}

				if (auto vde = dynamic_cast<VariableDeclarationExpression*>(exp))
				{
					get_nested_expressions(vde->get_expression(), expressions);
				}
				else if (auto conde_exp = dynamic_cast<ConditionalExpression*>(exp))
				{
					for (const auto& ie : conde_exp->get_if_body())
					{
						get_nested_expressions(ie.get(), expressions);
					}

					for (const auto& ee : conde_exp->get_else_body())
					{
						get_nested_expressions(ee.get(), expressions);
					}
				}
				else if (auto loop_exp = dynamic_cast<LoopExpression*>(exp))
				{
					for (const auto& be : loop_exp->get_body())
					{
						get_nested_expressions(be.get(), expressions);
					}
				}
				else if (auto ret_exp = dynamic_cast<ReturnExpression*>(exp))
				{
					get_nested_expressions(ret_exp->get_expression(), expressions);
				}
				else if (auto fde = dynamic_cast<FuncDeclarationExpression*>(exp))
				{
					for (const auto& body_exp : fde->get_body())
					{
						get_nested_expressions(body_exp.get(), expressions);
					}

					for (const auto& arg_exp : fde->get_args())
					{
						get_nested_expressions(arg_exp.get(), expressions);
					}
				}
				else if (auto fc_exp = dynamic_cast<FuncCallExpression*>(exp))
				{
					for (const auto& arg : fc_exp->get_args())
					{
						get_nested_expressions(arg.get(), expressions);
					}
				}
			}
		};

	}
}
