#include "source_file.h"

namespace elsa {
	namespace compiler {

		SourceFile::SourceFile(const char* filename)
		{
			read_file(filename);
		}

		wchar_t SourceFile::next_char()
		{
			return stream_.get();
		}

		bool SourceFile::good() const
		{
			return stream_.good();
		}

		void SourceFile::read_file(const char* filename)
		{
			std::wifstream f_stream(filename, std::ifstream::in);

			if (!f_stream.good())
				throw ElsaException("Could not open file");

			f_stream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

			stream_ << f_stream.rdbuf();
		}
	}
}
