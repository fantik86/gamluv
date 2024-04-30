#include "lexer.h"
#include "opcodes.h"
#include "executer.h"
#include "registers.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CHAR_COMMA ','
#define CHAR_SPACE ' '
#define CHAR_ENDLINE '\0'

void loadopcode(char* line, code_instruction* instruction) {

  char* opcode_str = (char*)malloc(32 * sizeof(char));
  for (int i = 0; line[i] != CHAR_ENDLINE; i++) {
    if (line[i] == CHAR_SPACE) {
      opcode_str[i] = CHAR_ENDLINE;
      instruction->opcode_index = (unsigned char)getopcodeindex(opcode_str);
      return;
    }
    opcode_str[i] = line[i];
  }
}

void loadarg2(char* line, int startpos,
	      code_instruction* instruction) {

  int result;
  char* char_arg2 = (char*)malloc(32 * sizeof(char));
  
  for (int i = startpos; line[i] != CHAR_ENDLINE; i++) {
    if (line[i] == ' ' || line[i] == CHAR_ENDLINE) {
      char_arg2[i] = CHAR_ENDLINE;
      result = atoi(char_arg2);
      
      if (!result)
	instruction->arg2 = (register_32*)find_register(char_arg2);
      else {
        instruction->arg2 = malloc(sizeof(int));
        *((int*)instruction->arg2) = result;
      }
      return;
    }
    /* [i - startpos] - appending chars from 0 index */
    char_arg2[i - startpos] = line[i]; 
  }
}

void loadargs(char* line, code_instruction* instruction) {
  
  int result;
  char* char_arg1 = (char*)malloc(32 * sizeof(char));
  char* opcode_name = opcode_table[instruction->opcode_index].name;
  int pos = strlen(opcode_name) + 1; /* Start position */
  int argscount = getopcodeargcount(instruction->opcode_index);

  if (argscount == 0) {
    fprintf(stderr, "Error: instruction have 0 arguments\n");
    return;
  }
  
  if (argscount >= 1) {

    for (; line[pos] != '\0'; pos++) {
      if (line[pos] == CHAR_COMMA) {

	char_arg1[pos] = '\0';

	result = atoi(char_arg1);

	if (!result) {
	  register_32* reg = (register_32*)find_register(char_arg1);
	  int* arg1 = instruction->arg1;
	  printf("%d\n", (int)(reg->value));
	} else {
	  instruction->arg1 = malloc(sizeof(int));
	  *((int*)instruction->arg1) = result;
	}
	if (argscount == 2)
	  loadarg2(line, pos+1, instruction);
	
	return;
      }
      if (line[pos] == ' ') 
	continue;

      char_arg1[pos - (strlen(opcode_name) + 1)] = line[pos];
    }
    
  }
}

int** readline(char* line) {
  
  code_instruction instruction;
  
  loadopcode(line, &instruction);
  loadargs(line, &instruction);
  //execute_instruction(&instruction);
  printf("instruction = {\n\t%hhu,\n\t%d,\n\t%d\n}\n", instruction.opcode_index, instruction.arg1, instruction.arg2);
}

/* Returns opcode index from opcode table */
unsigned char getopcodeindex(char* opcodestr) {
  for (int opcodeindex = 0; opcodeindex < OPCODES_MAX; opcodeindex++)
    if (opcode_table[opcodeindex].name &&
	strcmp(opcodestr, opcode_table[opcodeindex].name) == 0)
	return (unsigned char)opcodeindex;
}

unsigned char getopcodeargcount(unsigned char index) {
  return opcode_table[index].argument_count;
}

void readfile(FILE* file) {
  char* line = NULL;
  size_t len = 0;
  ssize_t read = getline(&line, &len, file);
  readline(line);
  if (feof(file) != 0) {
    printf("\n\nEOF\n");
    return;
  }
}
