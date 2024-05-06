#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registers.h"

char* register_names[REGISTERS_MAX] = {
  "A", "B", "AC"
};

asm_register* register_table[REGISTERS_MAX];

/* Type cast of value variable is necessary! */
int init_register(int index, bool isreadonly,
		  char* name, void* value) {

  if (index > REGISTERS_MAX)
    return 1;

  asm_register* reg = malloc(sizeof(asm_register));

  reg->isreadonly = isreadonly;
  reg->name = name;
  reg->value = value;
  
  register_table[index] = reg;
  return 0;
}

void* get_register_value(char* name) {
  for (int i = 0; i < REGISTERS_MAX; i++) {
    if (strcmp(((asm_register*)register_table[i])->name, name) == 0) {
      return &register_table[i]->value;
    }
  }
  return NULL;
}

void init_register_table(void) {
  for (int i = 0; i < REGISTERS_MAX; i++) {
    if (!register_names[i])
      break;
    
    init_register(i, false, register_names[i], NULL);
  }
}

void* find_register(char* register_name) {
  for (int i = 0; i < REGISTERS_MAX; i++) {
    if (strcmp(((asm_register*)register_table[i])->name, register_name))
      return register_table[i];
  }
  return NULL;
}
