#include <stdlib.h>
#include "registers.h"

void* register_table[REGISTERS_MAX];

void init_register_table() {
  register_table[0] = malloc(sizeof(register_32));
  ((register_32*)register_table[0])->name = "A";
  register_table[1] = malloc(sizeof(register_32));
  ((register_32*)register_table[0])->name = "B";
}
