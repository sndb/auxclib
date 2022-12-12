#include <stdbool.h>

struct btree;

struct btree *btree_new(void);
struct btree *btree_add(struct btree *t, int val);
struct btree *btree_remove(struct btree *t, int val);
bool btree_exists(struct btree *t, int val);
