#include <stdio.h>
#include "debug.h"
#include "lexer.h"
#include "types.h"

void instruction_print(code_instruction instruction, int type_arg1, int type_arg2) {
  if ((type_arg1 + type_arg2) == ASM_NOARGS) {
    printf("{\n\t%hhu,\n\t%p,\n\t%p\n}\n", instruction.opcode_index, instruction.arg1, instruction.arg2);
    return;
  }
  printf("{\n\t%hhu", instruction.opcode_index);
  switch (type_arg1) {
  case ASM_CHAR:
    printf(",\n\t%hhu", *(char*)instruction.arg1);
    break;
  case ASM_FLOAT:
    printf(",\n\t%f", *(float*)instruction.arg1);
    break;
  case ASM_INT:
    printf(",\n\t%d", *(int*)instruction.arg1);
    break;
  default:
    printf(",\n\t%p\n}\n", instruction.arg1);
    break;
  }
  switch (type_arg2) {
  case ASM_CHAR:
    printf(",\n\t%hhu\n}\n", *(char*)instruction.arg2);
    break;
  case ASM_FLOAT:
    printf(",\n\t%f\n}\n", *(float*)instruction.arg2);
    break;
  case ASM_INT:
    printf(",\n\t%d\n}\n", *(int*)instruction.arg2);
    break;
  default:
    printf(",\n\t%p\n}\n", instruction.arg2);
    break;
  }
}
