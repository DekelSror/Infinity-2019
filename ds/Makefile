#
#		just 'make' will compile in with debug flags
#		for release compilation, 'make mode=release'
#
# config

origin = $(shell pwd)
cc = gcc

mode ?= debug

ifeq ($(mode), release)
objs_dir = objs/release
lib_dir = lib/release
bin_dir = bin/release
cflags = -ansi -pedantic-errors -Wall -Wextra -g -DNDEBUG -O3

else
objs_dir = objs/debug
lib_dir = lib/debug
bin_dir = bin/debug
cflags = -ansi -pedantic-errors -Wall -Wextra -g
endif

names = bitarray circbuff linked_list dllist ilrd_uid sch_task priority_q\
vector stack scheduler queue bst avl_node avl hash heap sorted_ll dhcp

lib_name = libutils.a
lib_path = $(origin)/$(lib_dir)/$(lib_name)

# file names
modules_names = $(addsuffix .o,$(names))
test_file_names = $(addsuffix _test.o,$(names))
test_out_names = $(addsuffix .out,$(names))

# file names with relative path
modules = $(addprefix $(objs_dir)/,$(modules_names))
test_files = $(addprefix $(objs_dir)/,$(test_file_names))
tests_out = $(addprefix $(objs_dir)/,$(test_out_names))
#===============================================================================

# rules

all: libs $(tests_out)

libs: $(modules)
	ar r $(origin)/$(objs_dir)/$(lib_name) $?
	ln -sf $(origin)/$(objs_dir)/$(lib_name) $(lib_path)

# soft-link all headers
headers: folders
	rm -f headers/*.h
	ln -sf $(origin)/*/*.h $@

# create directory hierarchy
.PHONY: folders
folders:
	mkdir -p headers objs $(objs_dir) lib $(lib_dir) bin $(bin_dir)

# compile executables
$(objs_dir)/%.out: $(objs_dir)/%_test.o
	$(cc) $(cflags) -I$(origin)/headers $< $(lib_path) -o $@ -lm
	ln -sf $(origin)/$(objs_dir)/$*.out $(origin)/$(bin_dir)/$*.out

# compile objects
$(objs_dir)/%.o: $(origin)/*/%.c
	$(cc) $(cflags) -I$(origin)/headers -c $< -o $@ -lm
	$(cc) -I$(origin)/headers $< -MM -MT $@ -MF $(objs_dir)/$*.d

-include:($(modules:.o=.d))
-include:($(tests_out:.o=.d))

.PHONY: clean
clean:
	rm -rf objs lib bin headers
