#include "lexer.h"
#include "opcodes.h"
#include "executer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void loadopcode(char* line, code_instruction* instruction) {
  char* opcode = (char*)malloc(32 * sizeof(char));
  for (int i = 0; line[i] != '\0'; i++) {
    if (line[i] == ' ') {
      opcode[i] = '\0';
      instruction->opcode_index = (unsigned char)getopcodeindex(opcode);
      return;
    }
    opcode[i] = line[i];
    }
}

void loadarg2(char* line, int startpos, code_instruction* instruction) {
  char* char_arg2 = (char*)malloc(32 * sizeof(char));
  for (int i = startpos; line[i] != '\0'; i++) {
    if (line[i] == ' ' || line[i] == '\0') {
      char_arg2[i] = '\0';
      instruction->arg2 = atoi(char_arg2);
      return;
    }
    char_arg2[i - startpos] = line[i]; /* [i - startpos] - appending chars from 0 index */
  }
}

void loadargs(char* line, code_instruction* instruction) {
  int i;
  char* char_arg1 = (char*)malloc(32 * sizeof(char));
  int startpos = strlen(opcode_table[instruction->opcode_index].name) + 1;
  int argscount = getopcodeargcount(instruction->opcode_index);
  
  if (argscount >= 1) {
  
    for (i = startpos; line[i] != '\0'; i++) {
      if (line[i] == ',') {
	char_arg1[i] = '\0';
	instruction->arg1 = atoi(char_arg1);
	if (argscount == 2) {
	  loadarg2(line, i+1, instruction);
	}
	return;
      }
      if (line[i] == ' ') {
	continue;
      }
      char_arg1[i - startpos] = line[i];
    }
    
  }
}

int** readline(char* line) {
  /*
  typedef struct {          This is code_instruction structure from lexer.h, which is convenient :D
    unsigned char opcode;
    int arg1;
    int arg2;
  } code_instruction;
  */
  
  code_instruction instruction;
  
  loadopcode(line, &instruction);
  loadargs(line, &instruction);
  execute_instruction(&instruction);
  printf("instruction = {\n\t%hhu,\n\t%d,\n\t%d\n}\n", instruction.opcode_index, instruction.arg1, instruction.arg2);
}

/* Returns opcode index from opcode table */
unsigned char getopcodeindex(char* opcodestr) {
  for (int i = 0; i < OPCODES_MAX; i++) {
    if (opcode_table[i].name != NULL)
    if (strcmp(opcodestr, opcode_table[i].name) == 0) {
      return (unsigned char)i;
    }
  }
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
