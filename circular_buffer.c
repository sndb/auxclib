#include "circular_buffer.h"

#include <assert.h>
#include <stdlib.h>

struct circular_buffer *
cb_new(size_t n) {
	struct circular_buffer *cb = malloc(sizeof(struct circular_buffer));
	cb->data = malloc(sizeof(int[n]));
	cb->capacity = n;
	cb->start = cb->end = cb->count = 0;
	return cb;
}

void
cb_free(struct circular_buffer *cb) {
	free(cb->data);
	free(cb);
}

void
cb_put(struct circular_buffer *cb, int v) {
	assert(cb->count < cb->capacity);

	cb->data[cb->end] = v;
	cb->end++;
	cb->end %= cb->capacity;
	cb->count++;
}

int
cb_get(struct circular_buffer *cb) {
	assert(cb->count > 0);

	int v = cb->data[cb->start];
	cb->start++;
	cb->start %= cb->capacity;
	cb->count--;
	return v;
}
