#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>
#include <numeric>
#include <stddef.h>
#include <stdlib.h>

extern "C" {
#include "common.h"
#include "vector.h"
}

TEST(VectorTest, NewDefaultVector) {
	vector   *v;
	CC_status stat = new_vector(&v);
	EXPECT_EQ(stat, CC_ok);
}

TEST(VectorTest, NewVectorWithConfiguration) {
	vector     *v;
	vector_conf conf = {
	    .capacity = 2, .exp_factor = 2, .mem_alloc = malloc, .free_mem = free};
	CC_status stat = new_vector_with_conf(&v, &conf);
	EXPECT_EQ(stat, CC_ok);
}

TEST(VectorTest, DestroyVector) {
	vector   *v;
	CC_status stat = new_vector(&v);
	EXPECT_EQ(stat, CC_ok);
	destroy_vector(&v);
}

TEST(VectorTest, ExpandVectorCapacity) {
	vector   *v;
	CC_status stat = new_vector(&v);
	EXPECT_EQ(stat, CC_ok);
	size_t cap = maxsize(v);
	EXPECT_EQ(cap, VECTOR_DEFAULT_CAPACITY);
	stat = expand_capacity(v);
	EXPECT_EQ(stat, CC_ok);
	size_t newcap = maxsize(v);
	size_t ef     = expansion_factor(v);
	EXPECT_EQ(newcap, cap * ef);
	destroy_vector(&v);
}

TEST(VectorTest, PushBack) {
	vector   *v;
	CC_status stat = new_vector(&v);
	EXPECT_EQ(stat, CC_ok);
	int a = 12;
	stat  = push_back(v, (void *)&a);
	EXPECT_EQ(stat, CC_ok);
	size_t sz = size(v);
	EXPECT_EQ(sz, 1);
	destroy_vector(&v);
}

TEST(VectorTest, GetAtIndex) {
	vector   *v;
	CC_status stat = new_vector(&v);
	EXPECT_EQ(stat, CC_ok);
	int a = 12;
	stat  = push_back(v, (void *)&a);
	EXPECT_EQ(stat, CC_ok);
	size_t sz = size(v);
	EXPECT_EQ(sz, 1);
	int *temp;
	stat = get_at(v, 0, (void **)&temp);
	EXPECT_EQ(stat, CC_ok);
	EXPECT_EQ(*temp, a);
	destroy_vector(&v);
}

TEST(VectorTest, PushBackElems) {
	vector   *v;
	CC_status stat = new_vector(&v);
	EXPECT_EQ(stat, CC_ok);
	int a[100];
	for (int i = 0; i < 100; i++) {
		a[i] = i;
		stat = push_back(v, (void *)&a[i]);
		EXPECT_EQ(stat, CC_ok);
		int *a1;
		stat = get_at(v, i, (void **)&a1);
		EXPECT_EQ(stat, CC_ok);
		EXPECT_EQ(*a1, a[i]);
	}
}

TEST(VectorTest, PopBack) {
	vector   *v;
	CC_status stat = new_vector(&v);
	EXPECT_EQ(stat, CC_ok);
	int a = 12;
	stat  = push_back(v, (void *)&a);
	EXPECT_EQ(stat, CC_ok);
	size_t sz = size(v);
	EXPECT_EQ(sz, 1);
	stat = pop_back(v);
	EXPECT_EQ(stat, CC_ok);
	sz = size(v);
	EXPECT_EQ(sz, 0);
	destroy_vector(&v);
}

TEST(VectorTest, PopBackUnderflow) {
	vector   *v;
	CC_status stat = new_vector(&v);
	EXPECT_EQ(stat, CC_ok);
	stat = pop_back(v);
	EXPECT_EQ(stat, CC_underflow);
	destroy_vector(&v);
}

TEST(VectorTest, PushBackArray) {
	vector   *v;
	CC_status stat = new_vector(&v);
	EXPECT_EQ(stat, CC_ok);
	int arr[1000];
	std::iota(arr, arr + 1000, 0);
	stat = push_back_array(v, (void *)arr, sizeof(int), 1000);
	EXPECT_EQ(stat, CC_ok);
	for (int i = 0; i < 1000; i++) {
		int *a1;
		stat = get_at(v, i, (void **)&a1);
		EXPECT_EQ(stat, CC_ok);
		EXPECT_EQ(*a1, arr[i]);
	}
	destroy_vector(&v);
}

TEST(VectorTest, InsertAt) {
	vector   *v;
	CC_status stat = new_vector(&v);
	EXPECT_EQ(stat, CC_ok);

	int arr1[1001], arr2[1001];
	std::iota(arr1, arr1 + 1000, 0);

	stat = push_back_array(v, (void *)arr1, sizeof(int), 1000);
	EXPECT_EQ(stat, CC_ok);

	memcpy(arr2, arr1, 1000 * sizeof(int));
	memmove(arr2 + 21, arr2 + 20,
	        1000 * sizeof(arr2[0]) - 20 * sizeof(arr2[0]));

	int newval = 1001;
	arr2[20]   = newval;

	stat = insert_at(v, 20, (void *)&newval);

	EXPECT_EQ(stat, CC_ok);

	for (int i = 0; i < 1001; i++) {
		int *a1;
		stat = get_at(v, i, (void **)&a1);
		EXPECT_EQ(stat, CC_ok);
		EXPECT_EQ(*a1, arr2[i]);
	}

	destroy_vector(&v);
}

TEST(VectorTest, RemoveAt) {
	vector   *v;
	CC_status stat = new_vector(&v);
	EXPECT_EQ(stat, CC_ok);

	int arr1[1000], arr2[1000];
	std::iota(arr1, arr1 + 1000, 0);

	stat = push_back_array(v, (void *)arr1, sizeof(int), 1000);
	EXPECT_EQ(stat, CC_ok);

	memcpy(arr2, arr1, 1000 * sizeof(int));
	memmove(arr2 + 20, arr2 + 21, (1000 - 20 - 1) * sizeof(*arr2));
  
  stat = remove_at(v, 20);
	for (int i = 0; i < 999; i++) {
		int *a1;
		stat = get_at(v, i, (void **)&a1);
		EXPECT_EQ(stat, CC_ok);
		EXPECT_EQ(*a1, arr2[i]);
	}

	destroy_vector(&v);
}
