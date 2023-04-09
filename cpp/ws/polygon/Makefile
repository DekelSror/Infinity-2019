

CC = clang++


cppflags = -ansi -pedantic-errors -Wextra -Wall -g
target = polygon
names = point
ws_dir = ..

objs = $(addsuffix .o, $(names))
headers = $(addsuffix .hpp, $(names))



all: $(headers) $(objs)
	$(CC)  $(objs) $(target).cpp $(target)_test.cpp

%.o:
	$(CC)  $(ws_dir)/$*/$*.cpp -c -o $@

%.hpp:
	ln -sf $(ws_dir)/$*/$*.hpp $@
