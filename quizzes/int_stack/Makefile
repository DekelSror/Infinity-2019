



flags = -ansi -pedantic-errors -Wall -Wextra -g
ds_dir = ~/*/ds




all: stack.o
	gcc $(flags) stack.o istack.c istack_test.c

stack.o:
	ln -sf $(ds_dir)/stack.h stack.h
	gcc $(flags) -c $(ds_dir)/stack.c
