#ifndef OPCODES_H
#define OPCODES_H
#define OPCODES_MAX 256

void op_movi(void* a, void* b);
void op_addi(void* a, void* b);
void op_inci(void* a, void* b);
void op_subi(void* a, void* b);
void op_deci(void* a, void* b);

typedef struct {
  char* name;
  void (*function_ptr)(void*, void*);
  unsigned char argument_count;
} opcode;

extern opcode opcode_table[OPCODES_MAX];

#endif
