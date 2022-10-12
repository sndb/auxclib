#include "assert.h"
#include "bitmap.h"

#include <stdint.h>

static void
test_bitmap_new() {
	size_t len = 8;
	struct bitmap *bm = bitmap_new(len);

	assert(bm->len == len);
	for (size_t i = 0; i < len; i++)
		assert(bm->cells[i] == 0);

	bitmap_free(bm);
}

static void
test_bitmap_set_get() {
	size_t len = 8;
	struct bitmap *bm = bitmap_new(len);

	bitmap_set(bm, 0, true);
	assert(bitmap_get(bm, 0));

	bitmap_set(bm, 8 * 8 - 1, true);
	assert(bitmap_get(bm, 8 * 8 - 1));

	bitmap_set(bm, 3, true);
	assert(bitmap_get(bm, 3));

	bitmap_set(bm, 16, true);
	assert(bitmap_get(bm, 16));

	bitmap_set(bm, 0, false);
	assert(!bitmap_get(bm, 0));

	bitmap_set(bm, 8 * 8 - 1, false);
	assert(!bitmap_get(bm, 8 * 8 - 1));

	bitmap_set(bm, 3, false);
	assert(!bitmap_get(bm, 3));

	bitmap_set(bm, 16, false);
	assert(!bitmap_get(bm, 16));

	bitmap_free(bm);
}

static void
test_bitmap_and() {
	size_t len = 8;
	struct bitmap *bm = bitmap_new(len);
	struct bitmap *mask = bitmap_new(len);

	bitmap_set(mask, 0, true);
	bitmap_set(mask, 8 * 8 - 1, true);
	bitmap_set(mask, 33, true);

	bitmap_and(bm, mask);

	assert(!bitmap_get(bm, 0));
	assert(!bitmap_get(bm, 8 * 8 - 1));
	assert(!bitmap_get(bm, 33));

	bitmap_set(bm, 0, true);
	bitmap_set(bm, 8 * 8 - 1, true);
	bitmap_set(bm, 33, true);

	bitmap_and(bm, mask);

	assert(bitmap_get(bm, 0));
	assert(bitmap_get(bm, 8 * 8 - 1));
	assert(bitmap_get(bm, 33));

	bitmap_free(bm);
	bitmap_free(mask);
}

static void
test_bitmap_or() {
	size_t len = 8;
	struct bitmap *bm = bitmap_new(len);
	struct bitmap *mask = bitmap_new(len);

	bitmap_set(mask, 0, true);
	bitmap_set(mask, 8 * 8 - 1, true);
	bitmap_set(mask, 33, true);

	bitmap_or(bm, mask);

	assert(bitmap_get(bm, 0));
	assert(bitmap_get(bm, 8 * 8 - 1));
	assert(bitmap_get(bm, 33));

	bitmap_set(bm, 0, true);
	bitmap_set(bm, 8 * 8 - 1, true);
	bitmap_set(bm, 33, true);

	bitmap_or(bm, mask);

	assert(bitmap_get(bm, 0));
	assert(bitmap_get(bm, 8 * 8 - 1));
	assert(bitmap_get(bm, 33));

	bitmap_free(bm);
	bitmap_free(mask);
}

static void
test_bitmap_xor() {
	size_t len = 8;
	struct bitmap *bm = bitmap_new(len);
	struct bitmap *mask = bitmap_new(len);

	bitmap_set(mask, 0, true);
	bitmap_set(mask, 8 * 8 - 1, true);
	bitmap_set(mask, 33, true);

	bitmap_xor(bm, mask);

	assert(bitmap_get(bm, 0));
	assert(bitmap_get(bm, 8 * 8 - 1));
	assert(bitmap_get(bm, 33));

	bitmap_set(bm, 0, true);
	bitmap_set(bm, 8 * 8 - 1, true);
	bitmap_set(bm, 33, true);

	bitmap_xor(bm, mask);

	assert(!bitmap_get(bm, 0));
	assert(!bitmap_get(bm, 8 * 8 - 1));
	assert(!bitmap_get(bm, 33));

	bitmap_free(bm);
	bitmap_free(mask);
}

static void
test_bitmap_neg() {
	size_t len = 8;
	struct bitmap *bm = bitmap_new(len);

	bitmap_neg(bm);
	for (size_t i = 0; i < bm->len; i++)
		assert(bm->cells[i] == UINT8_MAX);

	bitmap_neg(bm);
	for (size_t i = 0; i < bm->len; i++)
		assert(bm->cells[i] == 0);

	bitmap_free(bm);
}

static void
test_bitmap_append() {
	size_t bm_len = 8;
	size_t tail_len = 4;
	struct bitmap *bm = bitmap_new(bm_len);
	struct bitmap *tail = bitmap_new(tail_len);

	bitmap_set(bm, 8 * 8 - 1, true);
	bitmap_set(bm, 0, true);
	bitmap_set(tail, 4 * 8 - 1, true);
	bitmap_set(tail, 0, true);
	bitmap_append(bm, tail);

	assert(bm->len == 12);
	assert(bitmap_get(bm, 0));
	assert(bitmap_get(bm, 4 * 8 - 1));
	assert(bitmap_get(bm, 4 * 8));
	assert(bitmap_get(bm, 12 * 8 - 1));

	assert(!bitmap_get(bm, 1));
	assert(!bitmap_get(bm, 4 * 8 - 2));
	assert(!bitmap_get(bm, 4 * 8 + 1));
	assert(!bitmap_get(bm, 12 * 8 - 2));

	bitmap_free(bm);
	bitmap_free(tail);
}

static void
test_bitmap_equal() {
	size_t len = 8;
	struct bitmap *a = bitmap_new(len);
	struct bitmap *b = bitmap_new(len);
	assert(bitmap_equal(a, b));
	bitmap_set(b, 8 * 8 - 1, true);
	assert(!bitmap_equal(a, b));
	bitmap_set(a, 8 * 8 - 1, true);
	assert(bitmap_equal(a, b));
	bitmap_set(b, 0, true);
	assert(!bitmap_equal(a, b));
	bitmap_set(a, 0, true);
	assert(bitmap_equal(a, b));
}

int
main(void) {
	test_bitmap_new();
	test_bitmap_set_get();
	test_bitmap_and();
	test_bitmap_or();
	test_bitmap_xor();
	test_bitmap_neg();
	test_bitmap_append();
	test_bitmap_equal();
}
