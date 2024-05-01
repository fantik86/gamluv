#include "opcodes.h"

void op_mov(int* a, int* b) {
  *(int*)a = *(int*)b;
}

void op_add(int* a, int* b) {
  *(int*)a += *(int*)b;
}

void op_inc(int* a, int* b) {
  *(int*)a++;
}

void op_sub(int* a, int* b) {
  *(int*)a -= *(int*)b;
}

void op_dec(int* a, int* b) {
  *(int*)a--;
}


opcode opcode_table[OPCODES_MAX] = { /* Opcode names and pointers to their functions */
  {"mov", op_mov, 2},
  {"add", op_add, 2},
  {"inc", op_inc, 1},
  {"sub", op_sub, 2},
  {"dec", op_dec, 1}
};
