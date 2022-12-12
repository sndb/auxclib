#include "binary_tree_struct.h"

#include <stdbool.h>
#include <stdlib.h>

struct btree *
btree_new(void)
{
	return NULL;
}

struct btree *
btree_add(struct btree *t, int val)
{
	if (!t) {
		struct btree *new = malloc(sizeof(*new));
		new->l = NULL;
		new->r = NULL;
		new->val = val;
		return new;
	}
	if (val < t->val)
		t->l = btree_add(t->l, val);
	else
		t->r = btree_add(t->r, val);
	return t;
}

struct btree *
btree_remove(struct btree *t, int val)
{
	if (!t)
		return NULL;
	if (t->val == val) {
		struct btree *l = t->l;
		struct btree *r = t->r;
		free(t);
		if (l) {
			struct btree *m = l;
			while (m->r)
				m = m->r;
			m->r = r;
		} else {
			l = r;
		}
		return l;
	}
	if (val < t->val)
		t->l = btree_remove(t->l, val);
	else
		t->r = btree_remove(t->r, val);
	return t;
}

bool
btree_exists(struct btree *t, int val)
{
	if (!t)
		return false;
	if (val == t->val)
		return true;
	if (val < t->val)
		return btree_exists(t->l, val);
	return btree_exists(t->r, val);
}
