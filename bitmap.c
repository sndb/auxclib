#include "bitmap.h"

#include "macros.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct bitmap *
bitmap_new(size_t len_bytes) {
	struct bitmap *bm = malloc(sizeof(struct bitmap));
	bm->cells = malloc(sizeof(uint8_t[len_bytes]));
	bm->len = len_bytes;
	bitmap_clear(bm);
	return bm;
}

void
bitmap_free(struct bitmap *bm) {
	free_all(bm->cells, bm);
}

void
bitmap_clear(struct bitmap *bm) {
	for (size_t i = 0; i < bm->len; i++)
		bm->cells[i] = 0;
}

static size_t
bitmap_cell_addr(const struct bitmap *bm, size_t n) {
	return bm->len - 1 - n / 8;
}

void
bitmap_set(struct bitmap *bm, size_t n, bool x) {
	size_t addr = bitmap_cell_addr(bm, n);
	if (x)
		bm->cells[addr] |= 1 << (n % 8);
	else
		bm->cells[addr] &= 0xFF ^ (1 << (n % 8));
}

bool
bitmap_get(const struct bitmap *bm, size_t n) {
	size_t addr = bitmap_cell_addr(bm, n);
	return (bm->cells[addr] & (1 << (n % 8))) > 0;
}

void
bitmap_and(struct bitmap *bm, const struct bitmap *mask) {
	assert(bm->len == mask->len);

	for (size_t i = 0; i < bm->len; i++)
		bm->cells[i] &= mask->cells[i];
}

void
bitmap_or(struct bitmap *bm, const struct bitmap *mask) {
	assert(bm->len == mask->len);

	for (size_t i = 0; i < bm->len; i++)
		bm->cells[i] |= mask->cells[i];
}

void
bitmap_xor(struct bitmap *bm, const struct bitmap *mask) {
	assert(bm->len == mask->len);

	for (size_t i = 0; i < bm->len; i++)
		bm->cells[i] ^= mask->cells[i];
}

void
bitmap_neg(struct bitmap *bm) {
	for (size_t i = 0; i < bm->len; i++)
		bm->cells[i] = ~bm->cells[i];
}

void
bitmap_append(struct bitmap *bm, const struct bitmap *tail) {
	bm->cells = realloc(bm->cells, sizeof(uint8_t[bm->len + tail->len]));
	for (size_t i = 0; i < tail->len; i++)
		bm->cells[bm->len + i] = tail->cells[i];
	bm->len += tail->len;
}

bool
bitmap_equal(const struct bitmap *a, const struct bitmap *b) {
	assert(a->len == b->len);
	for (size_t i = 0; i < a->len; i++)
		if (a->cells[i] != b->cells[i])
			return false;
	return true;
}
