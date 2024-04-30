#ifndef REGISTERS_H

#define REGISTERS_H
#define REGISTERS_MAX 128

typedef struct {
  char* name;
  unsigned char value;
} register_u8;

typedef struct {
  char* name;
  unsigned int value;
} register_u32;

typedef struct {
  char* name;
  char value;
} register_8;

typedef struct {
  char* name;
  float value;
} register_16;

typedef struct {
  char* name;
  int value;
} register_32;

void* find_register(char* register_name);
void init_register_table(void);

extern void* register_table[REGISTERS_MAX];

#endif
