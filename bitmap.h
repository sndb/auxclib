#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct bitmap {
	uint8_t *cells;
	size_t len;
};

struct bitmap *bitmap_new(size_t len_bytes);
void bitmap_free(struct bitmap *bm);
void bitmap_clear(struct bitmap *bm);
void bitmap_set(struct bitmap *bm, size_t n, bool x);
bool bitmap_get(const struct bitmap *bm, size_t n);
void bitmap_and(struct bitmap *bm, const struct bitmap *mask);
void bitmap_or(struct bitmap *bm, const struct bitmap *mask);
void bitmap_xor(struct bitmap *bm, const struct bitmap *mask);
void bitmap_neg(struct bitmap *bm);
void bitmap_append(struct bitmap *bm, const struct bitmap *tail);
bool bitmap_equal(const struct bitmap *a, const struct bitmap *b);
