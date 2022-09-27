#include <stdint.h>

#define funcApply(type, f, ...)                                    \
	{                                                          \
		void  *stopper = (int[]){0};                       \
		type **args    = (type *[]){__VA_ARGS__, stopper}; \
		for (int i = 0; args[i] != stopper; i++) {         \
			f(args[i]);                                \
		}                                                  \
	}

#define free_all(...) funcApply(void, free, __VA_ARGS__)

uint64_t djb2(const char *s);
uint64_t sdbm(const char *s);
