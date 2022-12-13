#include "hash_table.h"

#include <assert.h>
#include <stdio.h>

void
test_hash_table(void)
{
	struct hash_table *h = hash_table_new(3);
	const char *keys[] = {"123", "hello", "world", "asdfjklzxcv", "zzz"};
	int n = sizeof(keys) / sizeof(keys[0]);

	puts("add values");
	for (int i = 0; i < n; i++)
		hash_table_set(h, keys[i], i);

	puts("must exist");
	for (int i = 0; i < n; i++) {
		struct result r = hash_table_get(h, keys[i]);
		assert(r.ok);
		assert(r.value == i);
	}

	puts("must no exist");
	struct result r = hash_table_get(h, "jlkasdfjklasdfasfjlk");
	assert(!r.ok);

	puts("overwrite (old * 2)");
	for (int i = 0; i < n; i++) {
		struct result r = hash_table_get(h, keys[i]);
		assert(r.ok);
		assert(r.value == i);
		hash_table_set(h, keys[i], r.value * 2);
	}

	puts("check overwritten");
	for (int i = 0; i < n; i++) {
		struct result r = hash_table_get(h, keys[i]);
		assert(r.ok);
		assert(r.value == i * 2);
	}

	puts("delete");
	for (int i = 0; i < n; i++)
		hash_table_del(h, keys[i]);

	puts("check deleted");
	for (int i = 0; i < n; i++) {
		struct result r = hash_table_get(h, keys[i]);
		assert(!r.ok);
	}

	puts("free");
	hash_table_free(h);
}

int
main(void)
{
	test_hash_table();
}
