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

int
main(void) {
	test_max();
	test_min();
	test_between();
}
