#include "scoped_expression.h"

#include "func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		ScopedExpression::ScopedExpression(ScopedExpression* parent, FuncDeclarationExpression* root)
			:
			root_(root),
			parent_(parent)
		{}

		LocalTable& ScopedExpression::locals()
		{
			return locals_;
		}

		void ScopedExpression::add_arg(const std::wstring& name, const ElsaType& type)
		{
			add(name, type, nullptr, LocalType::Arg);
			root_->increment_num_args();
		}

		void ScopedExpression::add_arg(const std::wstring& name, const ElsaType& type, const StructDeclarationExpression* struct_expression)
		{
			add(name, type, struct_expression, LocalType::Arg);
			root_->increment_num_args();
		}

		void ScopedExpression::add_local(const std::wstring& name, const ElsaType& type)
		{
			add(name, type, nullptr, LocalType::Local);
			root_->increment_num_locals();
		}

		void ScopedExpression::add_local(const std::wstring& name, const ElsaType& type, const StructDeclarationExpression* struct_expression)
		{
			add(name, type, struct_expression, LocalType::Local);
			root_->increment_num_locals();
		}

		const LocalSymbol* ScopedExpression::get_local(const std::wstring& name)
		{
			const auto local = locals_.get(name);

			if (local == nullptr && parent_ != nullptr)
				return parent_->get_local(name);

			return local;
		}

		bool ScopedExpression::any_scope_has_local(const std::wstring & name)
		{
			return get_local(name) != nullptr;
		}

		bool ScopedExpression::has_local(const std::wstring & name)
		{
			return locals_.has_entry(name);
		}

		void ScopedExpression::add(const std::wstring& name, const ElsaType& type, const StructDeclarationExpression* struct_expression, LocalType local_type)
		{
			auto index = 0;
			if (local_type == LocalType::Local)
				index = root_->get_num_locals();
			else
				index = root_->get_num_args();

			locals_.add(name, new LocalSymbol(name, index, type, struct_expression, local_type));
		}

	}
}
