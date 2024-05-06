#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lexer.h"
#include "opcodes.h"
#include "executer.h"
#include "registers.h"
#include "debug.h"
#include "types.h"
#define CHAR_COMMA ','
#define CHAR_SPACE ' '
#define CHAR_ENDLINE '\0'
#define CHAR_NEWLINE '\n'

int write_instruction(char* line,
		code_instruction* instruction) {

  char* opcode_str = (char*)malloc(32 * sizeof(char));
  for (int i = 0; line[i] != CHAR_ENDLINE; i++) {
    if (line[i] == CHAR_SPACE) {
      opcode_str[i] = CHAR_ENDLINE;
      instruction->opcode_index = (uint8_t)getopcodeindex(opcode_str);

      write_arguments(line, strlen(opcode_str), instruction);
      free(opcode_str);
      return 0;
    }
    opcode_str[i] = line[i];
  }
  /* Opcode not found */
  free(opcode_str);
  return 1;
}

int loadarg2(char* line, int startpos,
	      code_instruction* instruction) {

  int* arg2;
  int result;
  asm_register* reg;
  char* char_arg2 = (char*)malloc(32 * sizeof(char));
  for (int i = 0; i < 32; i++)
    char_arg2[i] = CHAR_SPACE;
  
  for (int i = startpos; line[i] != CHAR_ENDLINE; i++) {
    if (line[i] == CHAR_SPACE || line[i] == CHAR_COMMA)
      continue;
	
    if (line[i] == CHAR_NEWLINE) {
      char_arg2[i] = CHAR_ENDLINE;
      result = atoi(char_arg2);
      if (!result) {
	reg = (asm_register*)find_register(char_arg2);
	instruction->arg2 = &reg->value;
      } else {
        arg2 = (int*)malloc(sizeof(int));
	*arg2 = result;
        instruction->arg2 = arg2;
      }
      free(char_arg2);
      return 0;
    }
    /* [i - startpos] - appending chars from 0 index */
    char_arg2[i - startpos] = line[i];
  }
  free(char_arg2);
  return 1;
}


int write_arguments(char* line, int startpos,
	      code_instruction* instruction) {
  
  int result;
  int* arg1;
  asm_register* reg;
  char* opcode_name = opcode_table[instruction->opcode_index].name;
  int pos = strlen(opcode_name) + 1; /* Start position */
  int argscount = getopcodeargcount(instruction->opcode_index);
  char* char_arg1 = (char*)malloc(32 * sizeof(char));
  for (int i = 0; i < 32; i++)
    char_arg1[i] = CHAR_SPACE;
  
  if (argscount == 0) {
    /* TODO: Add logic for 0 args instructions */
    return 1;
  }
  
  if (argscount >= 1) {
    for (; line[pos] != CHAR_ENDLINE; pos++) {
      
      if (line[pos] == CHAR_SPACE) 
	continue;
      
      if (line[pos] == CHAR_COMMA) {
	char_arg1[pos+1] = CHAR_ENDLINE;
	result = atoi(char_arg1);
	/* result = 0 means that argument is most likely register */
	if (!result) {
	  reg = (asm_register*)find_register(char_arg1);
	  instruction->arg1 = &reg->value;
	} else {
	  arg1 = (int*)malloc(sizeof(int));
	  *arg1 = result;
	  instruction->arg1 = arg1;
	}
	if (argscount == 2)
	  loadarg2(line, pos, instruction);
	
	free(char_arg1);
	return 0;
      }
      char_arg1[pos - (strlen(opcode_name) + 1)] = line[pos];
    }
  }
  free(char_arg1);
  return 1;
}

void asm_auto_read_line(char* line) {
  
  code_instruction instruction;
  
  write_instruction(line, &instruction);
  execute_instruction(&instruction);
  instruction_print(instruction, ASM_INT, ASM_INT);
}

/* Returns opcode index from opcode table */
uint8_t getopcodeindex(char* opcodestr) {
  for (int opcodeindex = 0; opcodeindex < OPCODES_MAX; opcodeindex++)
    if (opcode_table[opcodeindex].name &&
	strcmp(opcodestr, opcode_table[opcodeindex].name) == 0)
	return (uint8_t)opcodeindex;
  return 0;
}

uint8_t getopcodeargcount(uint8_t index) {
  if (opcode_table[index].argument_count)
    return opcode_table[index].argument_count;
  return 0;
}

void readfile(FILE* file) {
  char* line = NULL;
  size_t len = 0;
  getline(&line, &len, file);
  printf(line);
  asm_auto_read_line(line);
  
  if (feof(file)) {
    printf("\n\nEOF\n");
  }
  return;
}
