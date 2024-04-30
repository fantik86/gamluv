#include <stdio.h>

#ifndef LEXER_H_
#define LEXER_H_

typedef struct {
  unsigned char opcode_index;
  void* arg1;
  void* arg2;
} code_instruction;

void readfile(FILE* file);

int** readline(char* line);

unsigned char getopcodeindex(char* opcodestr);

unsigned char getopcodeargcount(unsigned char index);

#endif
