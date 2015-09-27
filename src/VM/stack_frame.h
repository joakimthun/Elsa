#pragma once

#include <cstddef>
#include <vector>

#include "types\object.h"
#include "constants\function_info.h"
#include "exceptions\runtime_exception.h"

namespace elsa {
	namespace vm {
		class GC;

		class StackFrame {
			friend class GC;

		public:
			StackFrame(FunctionInfo* function, std::size_t ret_addr, StackFrame* parent);
			~StackFrame();

			void push(Object o);
			Object pop();
			Object dump_top() const;
			bool has_stack_entries() const;
			Object load_local(std::size_t i) const;
			Object load_arg(std::size_t i) const;
			void store_local(std::size_t i, Object local);
			void store_arg(std::size_t i, Object arg);
			std::size_t get_ret_addr() const;
			StackFrame* get_parent() const;

		private:
			std::vector<Object> eval_stack_;
			Object* locals_;
			std::size_t locals_size_;
			std::size_t ret_addr_;
			FunctionInfo* function_;
			StackFrame* parent_;
		};

	}
}
