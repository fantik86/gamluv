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

void asm_auto_read_line(char* line);
  
uint8_t getopcodeindex(char* opcodestr);

uint8_t getopcodeargcount(uint8_t index);

int write_instruction(char* line,
	     code_instruction* instruction);

int write_arguments(char* line, int startpos,
	     code_instruction* instruction);

int loadarg2(char* line, int startpos,
	     code_instruction* instruction);

#endif
