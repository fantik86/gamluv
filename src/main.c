#include "lexer.h"
#include "opcodes.h"
#include "registers.h"
#include <stdio.h>

int main() {
  init_register_table();
  FILE* file = fopen("test.txt", "r");
  readfile(file);
}
