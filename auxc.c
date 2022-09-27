#include <stdint.h>

uint64_t
djb2(const char *s) {
	uint64_t hash = 5381;
	char     c;
	while ((c = *s++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}

uint64_t
sdbm(const char *s) {
	uint64_t hash = 0;
	char     c;
	while ((c = *s++))
		hash = c + (hash << 6) + (hash << 16) - hash;
	return hash;
}
