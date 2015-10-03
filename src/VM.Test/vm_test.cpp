#include "vm_test.h"

int vm_test() { return 0; };

int vmt1 = array_test();
int vmt2 = bool_opcodes_test();
int vmt3 = call_test();
int vmt4 = char_opcodes_test();
int vmt5 = float_opcodes_test();
int vmt6 = gc_test();
int vmt7 = int_opcodes_test();
int vmt8 = locals_test();
int vmt9 = recursive_call_test();
int vmt10 = string_opcodes_test();
int vmt11 = struct_test();
