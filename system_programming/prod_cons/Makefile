ds_dir = ../../ds
cflags = -ansi -pedantic-errors -Wextra -Wall -g -D_DEFAULT_SOURCE


names = prod_cons_1a prod_cons_1b prod_cons_1c prod_cons_2a\
		prod_cons_2b prod_cons_3b prod_cons_4

bins = $(addsuffix .out, $(names))

all: link $(bins)

%.out:
	$(CC) $(cflags) $*.c -o $@ -lpthread -lds


link:
	ln -sf $(ds_dir)/fsq/fsq.h fsq.h
	ln -sf $(ds_dir)/dllist/dllist.h dllist.h


clean:
	rm -rf $(bins) *.h libds.so
