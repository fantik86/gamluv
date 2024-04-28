#include <limits.h>
#include "lexer.h"
#include "opcodes.h"
#include "executer.h"

void execute_instruction(code_instruction instruction) {
  int min = INT_MIN;
  if (instruction.arg1 == INT_MIN) {
    opcode_table[instruction.opcode_index].function_ptr(&min, &min); /* No arguments */
  } else if (instruction.arg2 == INT_MIN) {
    opcode_table[instruction.opcode_index].function_ptr(&(instruction.arg1), &min); /* 1 argument */
  } else {
    opcode_table[instruction.opcode_index].function_ptr(&(instruction.arg1), &(instruction.arg2)); /* 2 arguments */    
  }
}
