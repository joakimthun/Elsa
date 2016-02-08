#include "scoped_expression.h"

#include "func_declaration_expression.h"

namespace elsa {
	namespace compiler {

		ScopedExpression::ScopedExpression(ScopedExpression* parent)
			:
			parent_(parent)
		{}

		LocalTable& ScopedExpression::locals()
		{
			return locals_;
		}

		void ScopedExpression::add_arg(const std::wstring& name, const ElsaType& type)
		{
			add(name, type, nullptr, LocalType::Arg);
			get_root_scope()->increment_num_args();
		}

		void ScopedExpression::add_arg(const std::wstring& name, const ElsaType& type, const StructDeclarationExpression* struct_expression)
		{
			add(name, type, struct_expression, LocalType::Arg);
			get_root_scope()->increment_num_args();
		}

		void ScopedExpression::add_local(const std::wstring& name, const ElsaType& type)
		{
			add(name, type, nullptr, LocalType::Local);
			get_root_scope()->increment_num_locals();
		}

		void ScopedExpression::add_local(const std::wstring& name, const ElsaType& type, const StructDeclarationExpression* struct_expression)
		{
			add(name, type, struct_expression, LocalType::Local);
			get_root_scope()->increment_num_locals();
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

		std::size_t ScopedExpression::create_new_local()
		{
			auto index = add(L"0", ElsaType(ObjectType::Object), nullptr, LocalType::Local);
			get_root_scope()->increment_num_locals();
			return index;
		}

		ScopedExpression* ScopedExpression::parent()
		{
			return parent_;
		}

		void ScopedExpression::accept(ExpressionVisitor * visitor)
		{
			throw ElsaException("Not implemented: ScopedExpression::accept");
		}

		FuncDeclarationExpression* ScopedExpression::get_root_scope()
		{
			if (parent_ == nullptr)
				return dynamic_cast<FuncDeclarationExpression*>(this);

			return parent_->get_root_scope();
		}

		std::size_t ScopedExpression::add(const std::wstring& name, const ElsaType& type, const StructDeclarationExpression* struct_expression, LocalType local_type)
		{
			std::size_t index = 0;
			if (local_type == LocalType::Local)
				index = get_root_scope()->get_num_locals();
			else
				index = get_root_scope()->get_num_args();

			locals_.add(name, new LocalSymbol(name, index, type, struct_expression, local_type));
			return index;
		}

	}
}
