#include <stdbool.h>
#include <stdlib.h>

struct node {
	const char *key;
	int value;
	struct node *next;
};

struct result {
	int value;
	bool ok;
};

struct hash_table {
	size_t n;
	struct node *buckets[];
};

struct hash_table *hash_table_new(size_t n);
void hash_table_free(struct hash_table *h);
void hash_table_set(struct hash_table *h, const char *key, int value);
void hash_table_del(struct hash_table *h, const char *key);
struct result hash_table_get(struct hash_table *h, const char *key);
