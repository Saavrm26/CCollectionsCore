#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int    a                = 10;
	float  b                = 11.0f;
	char   c                = 'a';
	void **composite_vector = malloc(3 * sizeof(void *));
	composite_vector[0]     = (void *)&a;
	composite_vector[1]     = (void *)&b;
	composite_vector[2]     = (void *)&c;
	assert(*((int *)composite_vector[0]) == a);
	assert(composite_vector[1] == &b);
	assert(composite_vector[2] == &c);
	free(composite_vector);
}
