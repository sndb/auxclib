#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void
die(const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

	fputc('\n', stderr);

	exit(EXIT_FAILURE);
}

void *
xmalloc(size_t size) {
	void *r = malloc(size);
	if (!r)
		die("Out of memory");
	return r;
}

void *
xcalloc(size_t count, size_t size) {
	void *r = calloc(count, size);
	if (!r)
		die("Out of memory");
	return r;
}

void *
xrealloc(void *ptr, size_t size) {
	void *r = realloc(ptr, size);
	if (!r)
		die("Out of memory");
	return r;
}
