

CC= g++ -ansi -pedantic-errors -Wextra -Wall -g


all:
	ln -sf ../../string/string.hpp string.hpp
	$(CC) ../../string/string.cpp -c
	$(CC) stack.cpp string.o stack_test.cpp
