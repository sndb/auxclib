#include <stdlib.h>
#include <sys/types.h>

struct vector {
	int *data;
	size_t capacity, length;
};

struct vector *vector_new();
void vector_free(struct vector *v);
void vector_expand(struct vector *v);
void vector_push(struct vector *v, int val);
int vector_get(const struct vector *v, size_t idx);
int vector_pop(struct vector *v);
ssize_t vector_index(const struct vector *v, int val);
void vector_clear(struct vector *v);
