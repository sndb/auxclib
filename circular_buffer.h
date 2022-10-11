#include <stdlib.h>

struct circular_buffer {
	int *data;
	size_t start, end, capacity, count;
};

struct circular_buffer *cb_new(size_t n);
void cb_free(struct circular_buffer *cb);
void cb_put(struct circular_buffer *cb, int v);
int cb_get(struct circular_buffer *cb);
