

STACK_DIR = ../../ds

MODULE = $(STACK_DIR)/stack.c
HEADER = $(STACK_DIR)/stack.h


all: lib
	gcc -g stack.o brackets.c -o brackets.out



lib:
	ln -sf $(HEADER) stack.h
	gcc -g -c $(MODULE) -o stack.o


clean:
	rm -rf *.h *.o *.out
