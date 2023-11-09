#ifndef VECTOR
#define VECTOR

#include "common.h"
#include <stddef.h>
typedef struct vector_conf {
	size_t capacity;
	size_t exp_factor;
	void *(*mem_alloc)(size_t size);
	void (*free_mem)(void *block);
} vector_conf;

#define VECTOR_DEFAULT_CAPACITY 8
#define VECTOR_DEFAULT_EXP_FACTOR 2
#define VECTOR_DEFAULT_MEM_ALLOCATOR malloc
#define VECTOR_DEFAULT_FREE_MEM free

#define VECTOR_CONF_DEFAULT                                                    \
	(vector_conf) {                                                            \
		.capacity   = VECTOR_DEFAULT_CAPACITY,                                 \
		.exp_factor = VECTOR_DEFAULT_EXP_FACTOR,                               \
		.mem_alloc  = VECTOR_DEFAULT_MEM_ALLOCATOR,                            \
		.free_mem   = VECTOR_DEFAULT_FREE_MEM                                  \
	}

typedef struct vector vector;

enum CC_status new_vector_with_conf(vector **out, vector_conf *conf);
enum CC_status new_vector(vector **out);

/*
 * free the memeory occupied by the vector, does not destroy the the contents of
 * arr
 *
 */
void destroy_vector(vector **target);

size_t size(vector *dest);

size_t maxsize(vector *dest);

size_t expansion_factor(vector *dest);

enum CC_status push_back(vector *dest, void *val_ptr);

enum CC_status pop_back(vector *dest);

enum CC_status get_at(vector *target, size_t idx, void **out);

enum CC_status
push_back_array(vector *dest, void *src, size_t step_size, size_t npos);

enum CC_status expand_capacity(vector *target);

enum CC_status insert_at(vector *dest, size_t idx, void *val_ptr);

enum CC_status remove_at(vector *dest, size_t idx);
#endif // !VECTOR
