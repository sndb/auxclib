#include "macros.h"

#include <assert.h>

void
test_max() {
	assert(MAX(-1, 1) == 1);
	assert(MAX(0, 10) == 10);
	assert(MAX(-1000000, 1000000) == 1000000);
	assert(MAX(-1.00, 1.00) == 1.00);
	assert(MAX(0.0, 123.456) == 123.456);
	assert(MAX(-1.23456, 1e20) == 1e20);
	assert(MAX(100 * 100, 100 * 100 + 1) == 10001);
	assert(MAX(42, 42) == 42);
	assert(MAX(-42, -42) == -42);
}

void
test_min() {
	assert(MIN(-1, 1) == -1);
	assert(MIN(0, 10) == 0);
	assert(MIN(-1000000, 1000000) == -1000000);
	assert(MIN(-1.00, 1.00) == -1.00);
	assert(MIN(0.0, 123.456) == 0);
	assert(MIN(-1.23456, 1e20) == -1.23456);
	assert(MIN(100 * 100, 100 * 100 + 1) == 10000);
	assert(MIN(42, 42) == 42);
	assert(MIN(-42, -42) == -42);
}

void
test_between() {
	assert(BETWEEN(5, 0, 10));
	assert(!BETWEEN(0, 5, 10));
	assert(!BETWEEN(10, 0, 5));
	assert(BETWEEN(2 * 2, 0, 4));
	assert(BETWEEN(2 * 2, 4, 8));
	assert(!BETWEEN(2 * 2, 4.1, 8));
	assert(!BETWEEN(2 * 2, 0, 3.9));
	assert(BETWEEN(1.0 / 3, 0.3, 0.4));
	assert(!BETWEEN(1.0 / 2, 0.3, 0.4));
}

void
test_array_size() {
	int a[] = {1, 2, 3, 4};
	assert(ARRAY_SIZE(a) == 4);
	int b[] = {0};
	assert(ARRAY_SIZE(b) == 1);
	int c[16384];
	assert(ARRAY_SIZE(c) == 16384);
}

struct container {
	int a;
	int b;
};

void
test_container_of() {
	struct container c1 = {1, 2};
	int *d = &c1.b;

	struct container *c2 = CONTAINER_OF(d, struct container, b);
	assert(c2->a == c1.a);
	assert(c2->b == c1.b);

	c2->a = 3;
	assert(c1.a == 3);
	assert(c1.b == 2);
	assert(c2->a == 3);
	assert(c2->b == 2);

	c2->b = 4;
	assert(c1.b == 4);
	assert(c2->b == 4);
	assert(*d == 4);
}

int
main(void) {
	test_max();
	test_min();
	test_between();
	test_array_size();
	test_container_of();
}
