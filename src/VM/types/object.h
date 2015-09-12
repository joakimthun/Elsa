#pragma once

#include "../exceptions/runtime_exception.h"

namespace elsa {
	namespace vm {

		enum OType {
			Undefined,
			Int,
			Float,
			Char,
			Bool,
			IPtr,
			FPtr,
			CPtr,
			BPtr,
		};

		typedef union {
			int i;
			float f;
			wchar_t c;
			bool b;
			void* ptr;
		} Value;

		class Object
		{
		public:
			Object();
			Object(int v);
			Object(float v);
			Object(wchar_t v);
			Object(void* ptr, OType type);

			int i() const;
			float f() const;
			wchar_t c() const;
			bool b() const;
			void* ptr() const;
			OType get_type() const;

		private:
			OType type_;
			Value value_;
		};

	}
}