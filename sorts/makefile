
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

ds_names = linked_list queue vector heap
ds_dir = ~/*/ds
ds_objs = $(addsuffix .o, $(ds_names))
ds_headers = $(addsuffix .h, $(ds_names))


all: lib
	$(CC) $(FLAGS) -I. -c sorts.c sorts_test.c
	$(CC) $(CFLAGS) -I. *.o

lib: $(ds_headers) $(ds_objs)
	ar r libsort.a $(ds_objs)

%.h:
	-ln -sf $(ds_dir)/$*/$@ $@


%.o:
	$(CC) $(FLAGS) -I. -c $(ds_dir)/$*/$*.c -o $@


clean:
	rm *.a *.out $(ds_objs) $(ds_headers)
