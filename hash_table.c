#include "hash_table.h"

#include "hash.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static struct node *
node_new(const char *key, int value)
{
	struct node *n = malloc(sizeof(*n));
	n->key = key;
	n->value = value;
	n->next = NULL;
	return n;
}

struct hash_table *
hash_table_new(size_t n)
{
	struct hash_table *h = malloc(sizeof(struct hash_table) + sizeof(struct node *[n]));
	memset(h->buckets, 0, sizeof(struct node *[n]));
	h->n = n;
	return h;
}

void
hash_table_free(struct hash_table *h)
{
	free(h);
}

void
hash_table_set(struct hash_table *h, const char *key, int value)
{
	size_t slot = djb2(key) % h->n;
	for (struct node *n = h->buckets[slot]; n; n = n->next) {
		if (strcmp(key, n->key) == 0) {
			n->value = value;
			return;
		}
	}
	struct node *n = node_new(key, value);
	n->next = h->buckets[slot];
	h->buckets[slot] = n;
}

void
hash_table_del(struct hash_table *h, const char *key)
{
	size_t slot = djb2(key) % h->n;
	struct node *prev = NULL;
	for (struct node *n = h->buckets[slot]; n; n = n->next) {
		if (strcmp(key, n->key) == 0) {
			struct node *next = n->next;
			free(n);
			if (prev)
				prev->next = next;
			else
				h->buckets[slot] = next;
		}
		prev = n;
	}
}

struct result
hash_table_get(struct hash_table *h, const char *key)
{
	size_t slot = djb2(key) % h->n;
	for (struct node *n = h->buckets[slot]; n; n = n->next)
		if (strcmp(key, n->key) == 0)
			return (struct result){n->value, true};
	return (struct result){0, false};
}
