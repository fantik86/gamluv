#ifndef REGISTERS_H

#define REGISTERS_H
#define REGISTERS_MAX 16
#include <stdbool.h>

/* NOTE: at 03.05.2024, isreadonly is not used. */
typedef struct {
  bool isreadonly;
  char* name;
  void* value;
} asm_register;

extern void* register_table[REGISTERS_MAX];

void* find_register(char* register_name);
void init_register_table(void);
int init_register(int index, bool isreadonly, char* name, void* value);
void* get_register_value(char* name);

#endif
