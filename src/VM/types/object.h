#pragma once

#include "otype.h"
#include "gcobject.h"
#include "../exceptions/runtime_exception.h"
#include "../constants/struct_info.h"

namespace elsa {
	namespace vm {

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
			Object(bool v);
			Object(GCObject* o);

			int i() const;
			float f() const;
			wchar_t c() const;
			bool b() const;
			GCObject* gco() const;
			OType get_type() const;
			void set_type(OType type);

		private:
			OType type_;
			Value value_;
		};

	}
}