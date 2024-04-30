all:
	gcc lexer.c opcodes.c executer.c registers.c main.c -g -o main
	./main

gdb:
	gdb main -ex run --batch
