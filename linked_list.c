#include "linked_list.h"

#include <assert.h>
#include <stdlib.h>

struct node *
node_new(int val)
{
	struct node *n = malloc(sizeof(*n));
	n->val = val;
	n->next = NULL;
	return n;
}

void
node_free(struct node *n)
{
	if (!n)
		return;
	struct node *next = n->next;
	free(n);
	node_free(next);
}

void
node_join(struct node *n, struct node *m)
{
	while (n->next)
		n = n->next;
	n->next = m;
}

struct node *
node_from_array(int arr[], size_t n)
{
	struct node *dummy = node_new(0);
	struct node *last = dummy;
	for (size_t i = 0; i < n; i++) {
		struct node *m = node_new(arr[i]);
		node_join(last, m);
		last = m;
	}
	struct node *first = dummy->next;
	free(dummy);
	return first;
}

int
node_pop(struct node **n)
{
	assert(*n);
	int val = (*n)->val;
	struct node *next = (*n)->next;
	free(*n);
	*n = next;
	return val;
}

struct node *
node_find(struct node *n, int val)
{
	while (n) {
		if (n->val == val)
			return n;
		n = n->next;
	}
	return NULL;
}

struct node *
node_nth(struct node *m, size_t n)
{
	for (size_t i = 0; i < n && m; i++)
		m = m->next;
	return m;
}

struct node *
node_last(struct node *n)
{
	while (n->next)
		n = n->next;
	return n;
}
