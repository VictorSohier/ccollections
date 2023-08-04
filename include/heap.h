#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef __HEAP_H
#define __HEAP_H
#ifndef define_heap
#define define_heap(T) \
	typedef struct { \
		T* array; \
		size_t length; \
		size_t capacity; \
		int8_t(*comparer)(const T* restrict a, const T* restrict b); \
		void*(*malloc)(size_t); \
		void*(*realloc)(void*, size_t); \
		void(*free)(void*); \
	} Heap_##T; \
	 \
	Heap_##T new_Heap_##T( \
		size_t capacity, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b) \
	) \
	{ \
		Heap_##T ret = { \
			.array = malloc(capacity * sizeof(T)), \
			.length = 0, \
			.capacity = capacity, \
			.comparer = comparer, \
			.malloc = malloc, \
			.realloc = realloc, \
			.free = free, \
		}; \
		return ret; \
	} \
	 \
	Heap_##T new_Heap_##T##_allocator( \
		size_t capacity, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b), \
		void*(*malloc)(size_t), \
		void*(*realloc)(void*, size_t), \
		void(*free)(void*) \
	) \
	{ \
		Heap_##T ret = { \
			.length = 0, \
			.capacity = capacity, \
			.comparer = comparer, \
			.malloc = malloc, \
			.realloc = realloc, \
			.free = free, \
		}; \
		ret.array = ret.malloc(capacity * sizeof(T)); \
		return ret; \
	} \
	 \
	void heapify_Heap_##T(Heap_##T* heap) \
	{ \
		size_t largest = 0; \
		size_t index; \
		size_t left; \
		size_t right; \
		size_t end = (heap->length/2) + 1; \
		for (size_t i = 0; i <= end; ++i) \
		{ \
			largest = end - i; \
			do \
			{ \
				index = largest; \
				largest = index; \
				left = 2 * index + 1; \
				right = 2 * index + 2; \
				if (left < heap->length && \
					heap->comparer(heap->array + left, \
					heap->array + largest) > 0) \
					largest = left; \
				if (left < heap->length && \
					heap->comparer(heap->array + right, \
					heap->array + largest) > 0) \
					largest = right; \
				swap_##T(heap->array + index, heap->array + largest); \
			} \
			while (index != largest & index >= 0); \
		} \
	} \
	 \
	T peek_Heap_##T(Heap_##T* heap) \
	{ \
		return *(heap->array); \
	} \
	 \
	T pop_Heap_##T(Heap_##T* heap) \
	{ \
		size_t index = 0; \
		T root = *(heap->array); \
		heap->length--; \
		T* ptr = heap->array; \
		*(ptr) = *(heap->array + heap->length); \
		T* a = heap->array + ((2 * index) + 1); \
		T* b = heap->array + ((2 * index) + 2); \
		while ( \
			(a < heap->array + heap->length) & \
			(b < heap->array + heap->length) && \
			(heap->comparer(ptr, a) < 0 | \
			heap->comparer(ptr, b) < 0) \
		) \
		{ \
			index = (2 * index); \
			if (heap->comparer(a, b) > 0)\
			{ \
				swap_##T(ptr, a); \
				index = index + 1; \
			} \
			else \
			{ \
				swap_##T(ptr, b); \
				index = index + 2; \
			} \
			ptr = heap->array + index; \
			a = heap->array + ((2 * index) + 1); \
			b = heap->array + ((2 * index) + 2); \
		} \
		return root; \
	} \
	 \
	void push_Heap_##T(Heap_##T* heap, T item) \
	{ \
		if (heap->length == heap->capacity) \
		{ \
			heap->capacity *= 2; \
			heap->array = realloc(heap->array, heap->capacity * sizeof(T)); \
		} \
		*(heap->array + heap->length) = item; \
		size_t index = heap->length; \
		heap->length++; \
		while ( \
			heap->comparer( \
				heap->array + index, \
				heap->array + ((index - 1) / 2) \
			) > 0 & \
			index != 0 \
		) \
		{ \
			swap_##T(heap->array + index, heap->array + ((index - 1) / 2)); \
			index = (index - 1) / 2; \
		} \
	}
#endif
#endif
