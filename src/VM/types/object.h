#pragma once

#include <stdlib.h>

#include "object_types\vm_type.h"
#include "gcobject.h"
#include "exceptions/runtime_exception.h"
#include "constants/struct_info.h"

namespace elsa {
	namespace vm {

		typedef union {
			int i;
			float f;
			wchar_t c;
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
			Object(bool v);

			int i() const;
			float f() const;
			wchar_t c() const;
			GCObject* gco() const;
			const Value& get_value() const;
			elsa::VMType get_type() const;
			void set_type(elsa::VMType type);

		private:
			elsa::VMType type_;
			Value value_;
		};

	}
}