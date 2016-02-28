#pragma once

#include <string>
#include <fstream>
#include <stdint.h>

#include "resource_handle.h"
#include "exceptions\runtime_exception.h"
#include "../memory/heap.h"
#include "../types/object.h"

namespace elsa {
	namespace vm {

		class FileHandle : public ResourceHandle
		{
		public:
			FileHandle(const std::wstring& path, int mode);
			~FileHandle();

			void close();
			bool good();
			int read(Object& arr, int num_bytes, Heap* heap);
			//void write();
			ResourceHandleType get_type() override;
		private:
			void assert_is_byte_array(const Object& arr);

			std::fstream file_;
		};
	}
}