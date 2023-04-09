



flags = -ansi -Wall -Wextra -pedantic-errors -O3 -g


all: link obj
	$(CC) $(cflags) -pg quick_sort.o word_sort.c -lpthread

link:
	ln -sf ../../sorts/quick_sort.h quick_sort.h

obj:
	$(CC) $(flags) -c ../../sorts/quick_sort.c -o quick_sort.o
