#include "binary_tree.h"

#include <assert.h>
#include <stdlib.h>

enum {
	N = 10,
};

void
test_btree(void)
{
	struct btree *t = btree_new();
	int values[N];
	for (int i = 0; i < N; i++)
		values[i] = rand();
	assert(!t);
	for (int i = 0; i < N; i++) {
		int v = values[i];
		assert(!btree_exists(t, v));
		t = btree_add(t, v);
		assert(btree_exists(t, v));
		t = btree_remove(t, v);
		assert(!btree_exists(t, v));
	}
	assert(!t);
}

int
main(void)
{
	test_btree();
	return 0;
}
