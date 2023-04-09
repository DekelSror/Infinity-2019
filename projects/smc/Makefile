#/*=============================================================================
# State Machine - Calculator
# Makefile
# Dekel Sror
# Review - Moti Zamir
# RC 1
#=============================================================================*/

origin = $(shell pwd)

flags = -ansi -pedantic-errors -Wextra -Wall -g

ds_dir = ../../ds/



all: links stack.o smc.o
	gcc $(flags) -I. -I./lib lib/*.o smc_test.c

stack.o:
	gcc $(flags) -c -I. -I./lib $(ds_dir)stack/stack.c -o lib/$@

smc.o:
	gcc $(flags) -c -I. -I./lib $*.c -o lib/$@

links:
	mkdir -p lib
	ln -sf $(ds_dir)utils/useful.h lib/useful.h
	ln -sf $(ds_dir)stack/stack.h lib/stack.h

clean:
	rm -rf ./lib a.out
