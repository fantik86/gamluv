#include <stdio.h>

#ifndef LEXER_H_
#define LEXER_H_

typedef struct {
  unsigned char opcode;
  int arg1;
  int arg2;
} code_instruction;

void readfile(FILE* file);

int** readline(char* line);

unsigned char getopcode(char* opcodestr);

unsigned char getopcodeargcount(unsigned char opcodeindex);

#endif
