all:
	gcc lexer.c opcodes.c executer.c registers.c main.c -Wall -g -o main
	./main

gdb:
	gdb main -ex run --batch
