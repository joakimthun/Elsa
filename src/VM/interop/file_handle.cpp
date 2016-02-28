#include "file_handle.h"

#include <iostream>

namespace elsa {
	namespace vm {

		FileHandle::FileHandle(const std::wstring& path, int mode)
		{
			int m = std::fstream::in;

			if (mode == 1 || mode == 2)
				m = m | std::fstream::out;

			file_.open(path, m | std::fstream::binary);
			if(!file_.is_open())
				throw RuntimeException(L"Could not open file '" + path + L"'");
		}

		FileHandle::~FileHandle()
		{
			close();
		}

		void FileHandle::close()
		{
			file_.close();
		}

		bool FileHandle::good()
		{
			return file_.good();
		}

		int FileHandle::read(Object& arr, int num_bytes, Heap* heap)
		{
			assert_is_byte_array(arr);
			auto buffer = new char[num_bytes];
			file_.read(buffer, num_bytes);
			auto num_read = file_.gcount();

			// Refactor this to avoid the loop, memcpy?
			for (auto i = 0; i < num_bytes; i++)
			{
				heap->add_element(arr, Object(static_cast<uint8_t>(buffer[i])));
			}

			delete[] buffer;
			return num_read;
		}

		ResourceHandleType FileHandle::get_type()
		{
			return ResourceHandleType::File;
		}

		void FileHandle::assert_is_byte_array(const Object& arr)
		{
			if (arr.gco() == nullptr || arr.gco()->type != GCObjectType::Array || arr.gco()->ai->type != VMType::Byte)
				throw RuntimeException("FileHandle::assert_is_byte_array");
		}
	}
}
