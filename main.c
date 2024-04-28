#include "lexer.h"
#include "opcodes.h"
#include <stdio.h>

int main() {
  FILE* file = fopen("test.txt", "r");
  readfile(file);
}
