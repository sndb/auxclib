#include <stdlib.h>

struct node {
	int val;
	struct node *next;
};

struct node *node_new(int val);
void node_free(struct node *n);
void node_join(struct node *n, struct node *m);
struct node *node_from_array(int arr[], size_t n);
int node_pop(struct node **n);
struct node *node_find(struct node *n, int val);
struct node *node_nth(struct node *m, size_t n);
struct node *node_last(struct node *n);
