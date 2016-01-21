#pragma once

#include <string>
#include <memory>

#include "expression.h"
#include "../types/elsa_type.h"

namespace elsa {
	namespace compiler {

		enum class ArgumentType
		{
			InstRef,
			UserDefined
		};

		class ArgumentExpression : public Expression
		{
		public:
			ArgumentExpression(ArgumentType arg_type = ArgumentType::UserDefined);
			ArgumentExpression(const std::wstring& name, const ElsaType* type);

			void set_name(const std::wstring& name);
			void set_type(ElsaType* type);

			const std::wstring& get_name() const;
			const ElsaType* get_type() const;
			const ArgumentType get_argument_type() const;

			void accept(ExpressionVisitor* visitor) override;

		private:
			std::wstring name_;
			std::unique_ptr<ElsaType> type_;
			ArgumentType argument_type_;
		};
	}
}
