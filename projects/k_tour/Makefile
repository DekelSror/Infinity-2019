# Knight's Tour
# Dekel Sror
# Makefile

ds_dir = ../../ds
quiz_dir = ../../quizzes
flags = -ansi -pedantic-errors -Wextra -Wall -g

debug: istack.o
	gcc $(flags) -I. *.o k_tour.c k_tour_test.c -o k_tour.out

release: istack.o
	gcc $(flags) -O3 -DNDEBUG -I. *.o k_tour.c k_tour_test.c -o k_tour.out

istack.o: stack.o
	ln -sf $(quiz_dir)/int_stack/$*.h $*.h
	gcc $(flags) -I. $(quiz_dir)/int_stack/$*.c -c -o $@

stack.o:
	ln -sf $(ds_dir)/$*/$*.h $*.h
	gcc $(flags) -I. $(ds_dir)/$*/$*.c -c -o $@

clean:
	rm *.o stack.h istack.h debug.txt
