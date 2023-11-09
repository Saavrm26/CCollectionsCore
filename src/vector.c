#include "vector.h"
#include "common.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/**
 * TODO: Fix destoy_vector
 * TODO: Rename the entire structure
 * */

struct vector {
	size_t size;
	size_t capacity;
	size_t exp_factor;
	void **arr;
	void *(*mem_alloc)(size_t size);
	void (*free_mem)(void *block);
};

enum CC_status new_vector_with_conf(vector **out, vector_conf *conf) {
	size_t ef;
	if (conf->exp_factor <= 1)
		return CC_invalid_expansion_factor;

	ef = conf->exp_factor;

	if (!conf->capacity || ef >= CC_MAX_ELEMENTS / conf->capacity)
		return CC_invalid_capacity;

	vector *v = conf->mem_alloc(sizeof(vector));
	if (!v)
		return CC_err_alloc;

	void **arr = conf->mem_alloc(conf->capacity * sizeof(void *));
	if (!arr) {
		conf->free_mem(v);
		return CC_err_alloc;
	}

	v->capacity   = conf->capacity;
	v->size       = 0;
	v->exp_factor = ef;
	v->arr        = arr;
	v->mem_alloc  = conf->mem_alloc;
	v->free_mem   = conf->free_mem;
	*out          = v;
	return CC_ok;
}

enum CC_status new_vector(vector **out) {
	vector_conf def = VECTOR_CONF_DEFAULT;
	return new_vector_with_conf(out, &def);
}

void destroy_vector(vector **target) {
	vector *v = *target;
	v->free_mem(v->arr);
	v->free_mem(v);
}

size_t maxsize(vector *dest) { return dest->capacity; }

size_t expansion_factor(vector *dest) { return dest->exp_factor; }

size_t size(vector *dest) { return dest->size; }

enum CC_status expand_capacity(vector *target) {
	if (target->capacity == CC_MAX_ELEMENTS)
		return CC_err_max_capacity;

	size_t new_cap = target->capacity * target->exp_factor;
	if (new_cap <= target->capacity)
		new_cap = CC_MAX_ELEMENTS;

	void **new_arr = target->mem_alloc(new_cap * sizeof(void *));
	if (!new_arr)
		return CC_err_alloc;

	memcpy(new_arr, target->arr, target->size * sizeof(void *));

	target->free_mem(target->arr);

	target->arr      = new_arr;
	target->capacity = new_cap;

	return CC_ok;
}

enum CC_status push_back(vector *dest, void *val_ptr) {
	size_t sz = dest->size;
	if (sz >= CC_MAX_ELEMENTS)
		return CC_err_max_capacity;
	if (sz == dest->capacity) {
		enum CC_status stat = expand_capacity(dest);
		if (stat != CC_ok)
			return stat;
	}

	dest->arr[sz] = val_ptr;
	dest->size++;

	return CC_ok;
}

enum CC_status pop_back(vector *dest) {
	if (!dest->size) {
		return CC_underflow;
	}
	dest->size--;
	return CC_ok;
}

enum CC_status get_at(vector *target, size_t idx, void **out) {
	if (idx > target->size)
		return CC_out_of_bounds;
	*out = target->arr[idx];
	return CC_ok;
}

enum CC_status
push_back_array(vector *dest, void *src, size_t step_size, size_t npos) {
	for (size_t pos = 0; pos < npos; pos++) {
		enum CC_status stat = push_back(dest, src);
		if (stat != CC_ok)
			return stat;
		src += step_size;
	}
	return CC_ok;
}

enum CC_status insert_at(vector *dest, size_t idx, void *val_ptr) {
	if (idx < 0 || idx > dest->size)
		return CC_out_of_bounds;
	enum CC_status stat;
	if (dest->size == dest->capacity) {
		stat = expand_capacity(dest);
		if (stat != CC_ok)
			return stat;
	}
	void **arr = dest->arr;
	memmove(arr + idx + 1, arr + idx, (dest->size - idx) * sizeof(*arr));
	arr[idx] = val_ptr;
	++dest->size;
	return CC_ok;
}

enum CC_status remove_at(vector *dest, size_t idx) {
	if (idx < 0 || idx >= dest->size)
		return CC_out_of_bounds;

	void **arr = dest->arr;
	memmove(arr + idx, arr + idx + 1, (dest->size - idx - 1) * sizeof(*arr));
	--dest->size;
	return CC_ok;
}
