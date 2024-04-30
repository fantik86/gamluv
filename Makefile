all:
	gcc lexer.c opcodes.c executer.c main.c -g -o main
	./main
