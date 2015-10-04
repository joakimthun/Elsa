#include "compiler_test.h"

int compiler_test() { return 0; }

int ct1 = lexer_test();
int ct2 = source_file_test();
int ct3 = parser_test();
