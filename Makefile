all: file

file:	
	gcc -Wall -std=c99 readFile.c parseFile.c library.c operations.c -Iinclude.h -o run