# System Programming - Simple WatchDog
# fork / exec and system
# Makefile
# Dekel Sror

names = wd_fork_exec wd_shell_command app wd_signal_handler wd_system
flags = -ansi -pedantic-errors -Wextra -Wall -g -D_POSIX_C_SOURCE

bins = $(addsuffix .out, $(names))

.PHONY: all
all: $(bins)


%.out : %.o
	$(CC) $(flags) $? -o $@

%.o: %.c
	$(CC) $(flags) $? -c -o $@

.PHONY: clean
clean:
	rm -f *.o *.out
