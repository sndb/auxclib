#include "linked_list.h"

#include <assert.h>
#include <stdio.h>

void
test_node_pop(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	struct node *n = node_from_array(arr, 5);

	int i = 1;
	while (n) {
		assert(node_pop(&n) == i);
		i++;
	}
}

void
test_node_join(void)
{
	int arr[3] = {1, 2, 3};
	int arr2[3] = {4, 5, 6};
	struct node *n = node_from_array(arr, 3);
	struct node *m = node_from_array(arr2, 3);
	node_join(n, m);
	int i = 1;
	for (struct node *k = n; k; k = k->next) {
		assert(k->val == i);
		i++;
	}
	node_free(n);
}

void
test_node_find(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	struct node *n = node_from_array(arr, 5);

	struct node *one = node_find(n, 1);
	assert(one->val == 1);

	struct node *four = node_find(n, 4);
	assert(four->val == 4);

	struct node *seven = node_find(n, 7);
	assert(!seven);

	node_free(n);
}

void
test_node_nth(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	struct node *n = node_from_array(arr, 5);

	struct node *first = node_nth(n, 0);
	assert(first->val == 1);

	struct node *fourth = node_nth(n, 3);
	assert(fourth->val == 4);

	struct node *eighth = node_nth(n, 7);
	assert(!eighth);

	node_free(n);
}

void
test_node_last(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	struct node *n = node_from_array(arr, 5);
	assert(node_last(n)->val == 5);
}

int
main(void)
{
	test_node_pop();
	test_node_join();
	test_node_find();
	test_node_nth();
	test_node_last();
}
