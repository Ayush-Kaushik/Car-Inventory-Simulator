all: file

file:	
	gcc -Wall -std=c99 library.c operations.c -Iinclude.h -o run