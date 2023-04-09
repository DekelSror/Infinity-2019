#/*=============================================================================
# Recursion
# Makefile
# Dekel Sror
# Review - Tzvi cubac
# RC 1
#=============================================================================*/

flags = -ansi -pedantic-errors -Wall -Wextra -g
ds_dir = ../../ds
istack_dir = ~/*/quizzes/int_stack


recursion.out: linked_list.o istack.o
	gcc $(flags) -Ilib/ lib/*.o $*.c $*_test.c

linked_list.o:
	mkdir -p lib
	ln -sf $(ds_dir)/$*.h lib/$*.h
	gcc $(flags) -c $(ds_dir)/$*.c -o lib/$@

istack.o: stack.o
	ln -sf $(istack_dir)/$*.h lib/$*.h
	gcc $(flags) -Ilib/ -c $(istack_dir)/$*.c -o lib/$@

clean:
	rm -rf lib
