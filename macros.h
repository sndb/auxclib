#define func_apply(type, f, ...)                                \
	{                                                       \
		void *stopper = (int[]){0};                     \
		type **args = (type *[]){__VA_ARGS__, stopper}; \
		for (int i = 0; args[i] != stopper; i++) {      \
			f(args[i]);                             \
		}                                               \
	}

#define free_all(...) func_apply(void, free, __VA_ARGS__)