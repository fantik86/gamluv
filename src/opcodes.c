#include <stdio.h>
#include <stdlib.h>
#include "opcodes.h"

void op_movi(void* a, void* b) {
  *(int*)a = *(int*)b;
}

void op_addi(void* a, void* b) {
  *(int*)a += *(int*)b;
}

void op_inci(void* a, void* b) {
  a++;
}

void op_subi(void* a, void* b) {
  *(int*)a -= *(int*)b;
}

void op_deci(void* a, void* b) {
  a--;
}


opcode opcode_table[OPCODES_MAX] = { /* Opcode names and pointers to their functions */
  {"movi", op_movi, 2},
  {"addi", op_addi, 2},
  {"inci", op_inci, 1},
  {"subi", op_subi, 2},
  {"deci", op_deci, 1}
};
