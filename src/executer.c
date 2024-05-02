#include <limits.h>
#include <stdio.h>
#include "lexer.h"
#include "opcodes.h"
#include "executer.h"

void execute_instruction(code_instruction* instruction) {
  int min = INT_MIN;
  int index = instruction->opcode_index;
  int* arg1_ptr = (int*)instruction->arg1;
  void (*opcode_call)();
  opcode_call = opcode_table[index].function_ptr;
  if (*(int*)instruction->arg1 == min)
    /* No arguments */
    opcode_call(&min, &min); 
  else if (*(int*)instruction->arg2 == min)
    /* 1 argument */
    opcode_call(instruction->arg1, &min); 
  else
    /* 2 arguments */
    opcode_call(instruction->arg1, instruction->arg2); 
}
