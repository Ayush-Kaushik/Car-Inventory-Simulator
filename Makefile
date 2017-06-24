all: file

file:	
	gcc -Wall -std=c99 library.c -Iinclude.h -o run