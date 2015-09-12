#pragma once

#include "../exceptions/runtime_exception.h"
#include "../constants/function_info.h"

namespace elsa {
	namespace vm {

		enum OType {
			Undefined,
			Int,
			Float,
			Char,
			Bool,
			GCOPtr,
		};

		struct GCObject
		{
			bool marked;
			void* ptr;
			FunctionInfo* fi;
		};

		typedef union {
			int i;
			float f;
			wchar_t c;
			bool b;
			GCObject* gco;
		} Value;

		class Object
		{
		public:
			Object();
			Object(int v);
			Object(float v);
			Object(wchar_t v);
			Object(GCObject* o);

			int i() const;
			float f() const;
			wchar_t c() const;
			bool b() const;
			GCObject* gco() const;
			OType get_type() const;

		private:
			OType type_;
			Value value_;
		};

	}
}