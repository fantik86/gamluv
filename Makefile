all:
	gcc lexer.c opcodes.c main.c -g -o main
	./main
