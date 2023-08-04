#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "pair.h"

#ifndef __BINARYTREE_H
#define __BINARYTREE_H

#ifndef __PAIR_SIZE_T_UINT8_T
#define __PAIR_SIZE_T_UINT8_T
define_pair(size_t, uint8_t);
#endif

#ifndef define_binarytree
#define define_binarytree(T) \
	typedef struct { \
		T value; \
		union { \
			uint8_t u8; \
			uint8_t unused : 7; \
			uint8_t populated : 1; \
		} flags; \
	} BinaryTreeNode_##T; \
	\
	typedef struct { \
		BinaryTreeNode_##T* array; \
		size_t count; \
		size_t capacity; \
		int8_t(*comparer)(const T* restrict a, const T* restrict b); \
		void*(*malloc)(size_t); \
		void*(*realloc)(void*, size_t); \
		void(*free)(void*); \
	} BinaryTree_##T; \
	 \
	BinaryTree_##T new_BinaryTree_##T##_allocator( \
		size_t capacity, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b), \
		void*(*customMalloc)(size_t), \
		void*(*customRealloc)(void*, size_t), \
		void(*customFree)(void*) \
	); \
	BinaryTree_##T new_BinaryTree_##T_init( \
		size_t count, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b), \
		T* array \
	); \
	BinaryTree_##T new_BinaryTree_##T_init_allocator( \
		size_t count, \
		T* array, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b), \
		void*(*customMalloc)(size_t), \
		void*(*customRealloc)(void*, size_t), \
		void(*customFree)(void*) \
	); \
	BinaryTree_##T new_BinaryTree_##T( \
		size_t capacity, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b) \
	); \
	BinaryTree_##T new_BinaryTree_##T##_init_handle( \
		size_t count, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b), \
		BinaryTreeNode_##T* array \
	); \
	BinaryTree_##T new_BinaryTree_##T##_init_handle_allocator( \
		size_t count, \
		BinaryTreeNode_##T* array, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b), \
		void*(*malloc)(size_t), \
		void*(*realloc)(void*, size_t), \
		void(*free)(void*) \
	); \
	void add_BinaryTree_##T( \
		BinaryTree_##T* tree, \
		T item \
	); \
	 \
	BinaryTree_##T new_BinaryTree_##T( \
		size_t capacity, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b) \
	) \
	{ \
		capacity = capacity ? capacity : 10; \
		BinaryTree_##T ret = { \
			.array = malloc(sizeof(BinaryTree_##T) * capacity), \
			.capacity = capacity, \
			.count = 0, \
			.malloc = malloc, \
			.realloc = realloc, \
			.free = free, \
		}; \
		return ret; \
	} \
	 \
	BinaryTree_##T new_BinaryTree_##T##_allocator( \
		size_t capacity, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b), \
		void*(*customMalloc)(size_t), \
		void*(*customRealloc)(void*, size_t), \
		void(*customFree)(void*) \
	) \
	{ \
		capacity = capacity ? capacity : 10; \
		BinaryTree_##T ret = { \
			.capacity = capacity, \
			.count = 0, \
			.comparer = comparer, \
			.malloc = customMalloc, \
			.realloc = customRealloc, \
			.free = customFree, \
		}; \
		ret.array = ret.malloc(ret.capacity * sizeof(BinaryTree_##T)); \
		return ret; \
	} \
	 \
	BinaryTree_##T new_BinaryTree_##T_init( \
		size_t count, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b), \
		T* array \
	) \
	{ \
		BinaryTree_##T ret = { \
			.array = malloc(count * sizeof(BinaryTree_##T)), \
			.capacity = count, \
			.count = count, \
			.comparer = comparer, \
			.malloc = malloc, \
			.realloc = realloc, \
			.free = free, \
		}; \
		T* endPtr = array + count; \
		ret.array = ret.malloc(count * sizeof(BinaryTree_##T)); \
		for (T* pT = array; pT < endPtr; ++pT) \
			add_BinaryTree_##T(&ret, *pT); \
		return ret; \
	} \
	 \
	BinaryTree_##T new_BinaryTree_##T_init_allocator( \
		size_t count, \
		T* array, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b), \
		void*(*customMalloc)(size_t), \
		void*(*customRealloc)(void*, size_t), \
		void(*customFree)(void*) \
	) \
	{ \
		BinaryTree_##T ret = { \
			.capacity = count, \
			.count = count, \
			.comparer = comparer, \
			.malloc = customMalloc, \
			.realloc = customRealloc, \
			.free = customFree, \
		}; \
		T* endPtr = array + count; \
		ret.array = ret.malloc(count * sizeof(BinaryTree_##T)); \
		for (T* pT = array; pT < endPtr; ++pT) \
			add_BinaryTree_##T(&ret, *pT); \
		return ret; \
	} \
	 \
	BinaryTree_##T new_BinaryTree_##T##_init_handle( \
		size_t count, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b), \
		BinaryTreeNode_##T* array \
	) \
	{ \
		BinaryTree_##T ret = { \
			.array = array, \
			.capacity = count, \
			.count = count, \
			.comparer = comparer, \
			.malloc = malloc, \
			.realloc = realloc, \
			.free = free, \
		}; \
		return ret; \
	} \
	 \
	BinaryTree_##T new_BinaryTree_##T##_init_handle_allocator( \
		size_t count, \
		BinaryTreeNode_##T* array, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b), \
		void*(*malloc)(size_t), \
		void*(*realloc)(void*, size_t), \
		void(*free)(void*) \
	) \
	{ \
		BinaryTree_##T ret = { \
			.array = array, \
			.capacity = count, \
			.count = count, \
			.comparer = comparer, \
			.malloc = malloc, \
			.realloc = realloc, \
			.free = free, \
		}; \
		return ret; \
	} \
	 \
	void add_BinaryTree_##T( \
		BinaryTree_##T* tree, \
		T item \
	) \
	{ \
		size_t index = 0; \
		uint16_t state = 0; \
		while (tree->array[index].flags.populated) \
		{ \
			state = (tree->array[index].flags.u8 << 8) | \
				(tree->comparer(&item, &(tree->array[index].value)) & 0x80); \
			switch (state) \
			{ \
				case (0x0080): \
				case (0x0000): \
				{ \
					tree->array[index].flags.populated = 1; \
					tree->array[index].value = item; \
					++(tree->count); \
					return; \
				} break; \
				case (0x0180): \
				{ \
					index = (index * 2) + 1; \
				} break; \
				case (0x0100): \
				{ \
					index = (index * 2) + 2; \
				} break; \
			} \
			if (index >= tree->capacity) \
			{ \
				tree->capacity *= 2; \
				tree->array = realloc( \
					tree->array, \
					tree->capacity * sizeof(BinaryTreeNode_##T) \
				); \
			} \
		} \
	} \

#endif
#endif //__BINARYTREE_H
