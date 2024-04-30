#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registers.h"

void* register_table[REGISTERS_MAX];

void init_register_table(void) {
  register_table[0] = malloc(sizeof(register_32));
  ((register_32*)register_table[0])->name = "A";

  register_table[1] = malloc(sizeof(register_32));
  ((register_32*)register_table[1])->name = "B";
}

void* find_register(char* register_name) {
  for (int i = 0; i < REGISTERS_MAX; i++) {
    if (strcmp(((register_32*)register_table[i])->name, register_name))
      return register_table[i];
    }
}
