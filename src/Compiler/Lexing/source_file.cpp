#include "source_file.h"

namespace elsa {
	namespace compiler {

		SourceFile::SourceFile(const wchar_t* filename)
		{
			file_name_ = std::wstring(filename);
			read_file(filename);
		}

		wchar_t SourceFile::next_char()
		{
			return stream_.get();
		}

		wchar_t SourceFile::peek_char()
		{
			return stream_.peek();
		}

		bool SourceFile::good() const
		{
			return stream_.good();
		}

		const std::wstring& SourceFile::get_file_name() const
		{
			return file_name_;
		}

		void SourceFile::read_file(const wchar_t* filename)
		{
			std::wifstream f_stream(filename, std::ifstream::in);

			if (!f_stream.good())
				throw ElsaException("Could not open file");

			f_stream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

			stream_ << f_stream.rdbuf();

			// If the file has a utf-8 byte order mark just skip it
			if (stream_.peek() == 65279)
				stream_.get();
		}
	}
}
