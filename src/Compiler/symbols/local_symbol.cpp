#include "local_symbol.h"

namespace elsa {
	namespace compiler {

		LocalSymbol::LocalSymbol(const std::wstring& name, std::size_t index, const ElsaType& type, LocalType local_type)
			:
			name_(name),
			index_(index),
			type_(type),
			struct_expression_(nullptr),
			local_type_(local_type)
		{}

		LocalSymbol::LocalSymbol(const std::wstring & name, std::size_t index, const ElsaType& type, const StructDeclarationExpression* struct_expression, LocalType local_type)
			:
			name_(name),
			index_(index),
			type_(type),
			struct_expression_(struct_expression),
			local_type_(local_type)
		{
		}

		const std::wstring& LocalSymbol::get_name() const
		{
			return name_;
		}

		std::size_t LocalSymbol::get_index() const
		{
			return index_;
		}

		const ElsaType& LocalSymbol::get_type() const
		{
			return type_;
		}

		LocalType LocalSymbol::get_local_type() const
		{
			return local_type_;
		}

		const StructDeclarationExpression * LocalSymbol::get_struct_expression() const
		{
			return struct_expression_;
		}

	}
}
