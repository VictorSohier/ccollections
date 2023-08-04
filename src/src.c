#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/binaryTree.h"
#include "../include/heap.h"
#include "../include/list.h"
#include "../include/pair.h"
#include "../include/swap.h"

#ifndef __PAIR_INT64_T_UINT8_T
#define __PAIR_INT64_T_UINT8_T
define_pair(int64_t, uint8_t);
#endif

#ifndef __SWAP_INT64_t
#define __SWAP_INT64_T
define_swap(int64_t);
#endif

#ifndef __HEAP_INT64_T
#define __HEAP_INT64_T
define_heap(int64_t);
#endif

#ifndef __LIST_INT64_T
#define __LIST_INT64_T
define_list(int64_t);
#endif

#ifndef __BINARYTREE_INT64_T
#define __BINARYTREE_INT64_T
define_binarytree(int64_t);
#endif

int8_t min_compare_int64_t(
	const int64_t* restrict a,
	const int64_t* restrict b
)
{
    return ((*b - *a) >> 63) + (((*a - *b) >> 63) * -1);
}

int8_t compare_int64_t(
	const int64_t* restrict a,
	const int64_t* restrict b
)
{
    return ((*a - *b) >> 63) + (((*b - *a) >> 63) * -1);
}

int main(void)
{
	srand(time(0));

	List_int64_t list = new_List_int64_t_allocator(
		10,
		malloc,
		realloc,
		free
	);
	for (size_t i = 0; i < 100; ++i)
		add_List_int64_t(&list, rand());

	List_int64_t list2 = new_List_T_init_allocator(
		list.length,
		list.array,
		malloc,
		realloc,
		free
	);
	sort_List_int64_t(&list, compare_int64_t);

	int64_t* endPtr = list.array + list.length;
	for (int64_t* p = list.array; p != endPtr; ++p)
		printf("%ld\n", *p);
	endPtr = list2.array + list.length;
	/* for (int64_t* p = list2.array; p != endPtr; ++p) */
	/* 	printf("%ld\n", *p); */
	uint8_t elementsExist = 1;
	for (int64_t* p = list2.array; p != endPtr; ++p)
	{
		elementsExist &= binarySearch_List_int64_t(&list, *p, compare_int64_t)
			.second;
	}
	printf("%d\n", elementsExist);
	free_List_int64_t(&list);
	free_List_int64_t(&list2);
}
