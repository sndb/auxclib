#include "vector.h"

#include <assert.h>

void
test_vector_new() {
	struct vector *v = vector_new();
	assert(v->length == 0);
	assert(v->capacity != 0);
	vector_free(v);
}

void
test_vector_expand() {
	struct vector *v = vector_new();
	size_t cap = v->capacity;
	vector_expand(v);
	assert(v->capacity > cap);
	vector_free(v);
}

void
test_vector_push_pop() {
	struct vector *v = vector_new();
	for (int i = 0; i < 1000; i++)
		vector_push(v, i);
	for (int i = 999; i >= 0; i--)
		assert(vector_pop(v) == i);
	for (int i = 0; i < 1000; i++)
		assert(vector_pop(v) == 0);
	vector_free(v);
}

void
test_vector_index() {
	struct vector *v = vector_new();
	for (int i = 0; i < 1000; i++)
		vector_push(v, i);
	for (int i = 0; i < 1000; i++)
		assert(vector_index(v, i) == i);
	vector_clear(v);
	for (int i = 0; i < 100; i++)
		vector_push(v, i * 1000);
	for (int i = 0; i < 100; i++)
		assert(vector_index(v, i * 1000) == i);
	for (int i = 0; i < 50; i++)
		vector_pop(v);
	for (int i = 50; i < 100; i++)
		assert(vector_index(v, i) == -1);
	vector_free(v);
}

void
test_vector_get() {
	struct vector *v = vector_new();
	for (int i = 0; i < 100; i++)
		vector_push(v, i);
	for (int i = 0; i < 100; i++)
		assert(vector_get(v, i) == i);
	vector_free(v);
}

int
main(void) {
	test_vector_new();
	test_vector_expand();
	test_vector_push_pop();
	test_vector_index();
	test_vector_get();
}
