#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void** iterate(void *src, size_t step_size, size_t npos) {
  void **vector = malloc(npos * sizeof(void *));
  for (size_t pos = 0; pos < npos; pos++) {
    vector[pos] = src;
    src += step_size;
  }
  return vector;
}

int main() {
	// int    a                = 10;
	// float  b                = 11.0f;
	// char   c                = 'a';
	// void **composite_vector = malloc(3 * sizeof(void *));
	// composite_vector[0]     = (void *)&a;
	// composite_vector[1]     = (void *)&b;
	// composite_vector[2]     = (void *)&c;
	// assert(*((int *)composite_vector[0]) == a);
	// assert(composite_vector[1] == &b);
	// assert(composite_vector[2] == &c);
	// free(composite_vector);
  int arr[3] = {1, 2, 3};
  void ** vector = iterate((void *)arr, sizeof(int), 3);
  for (int i = 0; i < 3; i++) {
    assert((int *)vector[i] == &arr[i]);
    assert(*(int *)vector[i] == arr[i]);
  }
  free(vector);
}
