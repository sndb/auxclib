#include "vector.h"

#include <stdlib.h>
#include <sys/types.h>

struct vector *
vector_new() {
	struct vector *v = malloc(sizeof(struct vector));
	v->capacity = 32;
	v->length = 0;
	v->data = malloc(sizeof(int[v->capacity]));
	return v;
}

void
vector_free(struct vector *v) {
	free(v->data);
	free(v);
}

void
vector_expand(struct vector *v) {
	v->capacity *= 2;
	v->data = realloc(v->data, sizeof(int[v->capacity]));
}

void
vector_push(struct vector *v, int val) {
	if (v->capacity == v->length)
		vector_expand(v);
	v->data[v->length] = val;
	v->length++;
}

int
vector_pop(struct vector *v) {
	if (v->length == 0)
		return 0;
	v->length--;
	return v->data[v->length];
}

int
vector_get(const struct vector *v, size_t idx) {
	if (idx >= v->length)
		return 0;
	return v->data[idx];
}

ssize_t
vector_index(const struct vector *v, int val) {
	for (size_t i = 0; i < v->length; i++)
		if (v->data[i] == val)
			return i;
	return -1;
}

void
vector_clear(struct vector *v) {
	v->length = 0;
}
