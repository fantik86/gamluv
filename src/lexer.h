#include <stdio.h>
#include <stdint.h>

#ifndef LEXER_H
#define LEXER_H

typedef struct {
  uint8_t opcode_index;
  void* arg1;
  void* arg2;
} code_instruction;

void readfile(FILE* file);

void readline(char* line);

uint8_t getopcodeindex(char* opcodestr);

uint8_t getopcodeargcount(uint8_t index);

int loadargs(char* line, code_instruction* instruction);

#endif
