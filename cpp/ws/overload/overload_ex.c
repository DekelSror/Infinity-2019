#include <dlfcn.h>
#include <stdio.h>

int main(void)
{
	void *lib = dlopen("./liboverpp.so", RTLD_LAZY);
	void *sym = dlsym(lib, "Foo");

	printf("lib %p sym %p\n", lib, sym);

	return 0;
}
