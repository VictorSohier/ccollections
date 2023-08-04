#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "pair.h"

#ifndef __LIST_H
#define __LIST_H

#ifndef __PAIR_SIZE_T_UINT8_T
#define __PAIR_SIZE_T_UINT8_T
define_pair(size_t, uint8_t);
#endif

#ifndef define_list
#define define_list(T) \
	typedef struct { \
		T* array; \
		size_t length; \
		size_t capacity; \
		void*(*malloc)(size_t); \
		void*(*realloc)(void*, size_t); \
		void(*free)(void*); \
	} List_##T; \
	 \
	List_##T new_List_##T(size_t capacity); \
	List_##T new_List_##T##_allocator( \
		size_t capacity, \
		void*(*customMalloc)(size_t), \
		void*(*customRealloc)(void*, size_t), \
		void(*customFree)(void*) \
	); \
	List_##T new_List_##T_init(size_t count, T* array); \
	List_##T new_List_##T_init_allocator( \
		size_t count, \
		T* array, \
		void*(*customMalloc)(size_t), \
		void*(*customRealloc)(void*, size_t), \
		void(*customFree)(void*) \
	); \
	List_##T new_List_##T##_init_handle(size_t count, T* array); \
	List_##T new_List_##T##_init_handle_allocator( \
		size_t count, \
		T* array, \
		void*(*malloc)(size_t), \
		void*(*realloc)(void*, size_t), \
		void(*free)(void*) \
	); \
	void add_List_##T(List_##T* list, T item); \
	void addRange_List_##T(List_##T* list, T* items, size_t count); \
	uint8_t remove_List_##T(List_##T* list, T item); \
	uint8_t removeAt_List_##T(List_##T* list, size_t index); \
	uint8_t removeWithDeleter_List_##T( \
		List_##T* list, \
		T item, \
		void* state, \
		void(*deleter)(void* state, T* item) \
	); \
	uint8_t removeAtWithDeleter_List_##T( \
		List_##T* list, \
		size_t index, \
		void* state, \
		void(*deleter)(void* state, T* item) \
	); \
	pair_size_t_uint8_t indexOf_List_##T(List_##T* list, T item); \
	pair_size_t_uint8_t lastIndexOf_List_##T(List_##T* list, T item); \
	void clear_List_##T(List_##T* list); \
	void clearWithDeleter_List_##T( \
		List_##T* list, \
		void* state, \
		void(*deleter)(void* state, T* item) \
	); \
	void insert_List_##T(List_##T* list, size_t index, T item); \
	void insertRange_List_##T( \
		List_##T* list, \
		size_t index, \
		T* items, \
		size_t count \
	); \
	void forEach_List_##T( \
		List_##T* list, \
		void* state, \
		void(*action)(void* state, T* item) \
	); \
	void free_List_##T( \
		List_##T* list \
	); \
	void freeListWithDeleter_List_##T( \
		List_##T* list, \
		void* state, \
		void(*deleter)(void* state, T* item) \
	); \
	uint8_t set_List_##T(List_##T* list, T item, size_t index); \
	pair_##T##_uint8_t get_List_##T(List_##T* list, size_t index); \
	pair_size_t_uint8_t getRef_List_##T(List_##T* list, size_t index); \
	void sort_List_##T( \
		List_##T* list, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b) \
	); \
	pair_size_t_uint8_t binarySearch_List_##T( \
		List_##T* list, \
		T item, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b) \
	); \
	 \
	List_##T new_List_##T(size_t capacity) \
	{ \
		capacity = capacity ? capacity : 10; \
		List_##T ret = { \
			.array = malloc(sizeof(T) * capacity), \
			.capacity = capacity, \
			.length = 0, \
			.malloc = malloc, \
			.realloc = realloc, \
			.free = free, \
		}; \
		return ret; \
	} \
	 \
	List_##T new_List_##T##_allocator( \
		size_t capacity, \
		void*(*customMalloc)(size_t), \
		void*(*customRealloc)(void*, size_t), \
		void(*customFree)(void*) \
	) \
	{ \
		capacity = capacity ? capacity : 10; \
		List_##T ret = { \
			.capacity = capacity, \
			.length = 0, \
			.malloc = customMalloc, \
			.realloc = customRealloc, \
			.free = customFree, \
		}; \
		ret.array = ret.malloc(ret.capacity * sizeof(T)); \
		return ret; \
	} \
	 \
	List_##T new_List_##T_init(size_t count, T* array) \
	{ \
		List_##T ret = { \
			.array = malloc(count * sizeof(T)), \
			.capacity = count, \
			.length = count, \
			.malloc = malloc, \
			.realloc = realloc, \
			.free = free, \
		}; \
		memcpy(ret.array, array, count * sizeof(T)); \
		return ret; \
	} \
	 \
	List_##T new_List_##T_init_allocator( \
		size_t count, \
		T* array, \
		void*(*customMalloc)(size_t), \
		void*(*customRealloc)(void*, size_t), \
		void(*customFree)(void*) \
	) \
	{ \
		List_##T ret = { \
			.capacity = count, \
			.length = count, \
			.malloc = customMalloc, \
			.realloc = customRealloc, \
			.free = customFree, \
		}; \
		ret.array = ret.malloc(count * sizeof(T)); \
		memcpy(ret.array, array, count * sizeof(T)); \
		return ret; \
	} \
	 \
	List_##T new_List_##T##_init_handle(size_t count, T* array) \
	{ \
		List_##T ret = { \
			.array = array, \
			.capacity = count, \
			.length = count, \
			.malloc = malloc, \
			.realloc = realloc, \
			.free = free, \
		}; \
		return ret; \
	} \
	 \
	List_##T new_List_##T##_init_handle_allocator( \
		size_t count, \
		T* array, \
		void*(*malloc)(size_t), \
		void*(*realloc)(void*, size_t), \
		void(*free)(void*) \
	) \
	{ \
		List_##T ret = { \
			.array = array, \
			.capacity = count, \
			.length = count, \
			.malloc = malloc, \
			.realloc = realloc, \
			.free = free, \
		}; \
		return ret; \
	} \
	 \
	void add_List_##T(List_##T* list, T item) \
	{ \
		if (list->length == list->capacity) \
		{ \
			list->capacity *= 2; \
			list->array = list->realloc( \
				list->array, \
				list->capacity * sizeof(T) \
			); \
		} \
		*(list->array + list->length) = item; \
		list->length++; \
	} \
	 \
	void addRange_List_##T(List_##T* list, T* items, size_t count) \
	{ \
		while ((list->capacity - list->length) < count) list->capacity *= 2; \
		list->array = list->realloc(list->array, list->capacity * sizeof(T)); \
		memmove(list->array + list->length, items, count * sizeof(T)); \
		list->length += count; \
	} \
	 \
	uint8_t remove_List_##T(List_##T* list, T item) \
	{ \
		uint8_t shouldRemove = 1; \
		uint8_t* a = (uint8_t*) &item; \
		uint8_t* b; \
		for (size_t i = 0; i < list->length; i++) \
		{ \
			b = (uint8_t*) (list->array + i); \
			for (size_t j = 0; j < sizeof(T); j++) \
			{ \
				shouldRemove &= *(a) == *(b); \
				a++; \
				b++; \
			} \
			if (shouldRemove) \
			{ \
				T* dest = list->array + i; \
				size_t count = (list->capacity - i) * sizeof(T); \
				memmove(dest, dest + 1, count); \
				list->length--; \
				return 1; \
			} \
			else \
			{ \
				shouldRemove = 1; \
				a = (uint8_t*) &item; \
			} \
		} \
		return 0; \
	} \
	 \
	uint8_t removeAt_List_##T(List_##T* list, size_t index) \
	{ \
		if (index < list->length) \
		{ \
			T* dest = list->array + index; \
			size_t count = (list->capacity - index) * sizeof(T); \
			memmove(dest, dest + 1, count); \
			list->length--; \
			return 1; \
		} \
		return 0; \
	} \
	 \
	uint8_t removeWithDeleter_List_##T( \
		List_##T* list, \
		T item, \
		void* state, \
		void(*deleter)(void* state, T* item) \
	) \
	{ \
		uint8_t shouldRemove = 1; \
		uint8_t* a = (uint8_t*) &item; \
		uint8_t* b; \
		for (size_t i = 0; i < list->length; i++) \
		{ \
			b = (uint8_t*) (list->array + i); \
			for (size_t j = 0; j < sizeof(T); j++) \
			{ \
				shouldRemove &= *(a) == *(b); \
				a++; \
				b++; \
			} \
			if (shouldRemove) \
			{ \
				T* dest = list->array + i; \
				deleter(state, dest); \
				size_t count = (list->capacity - i) * sizeof(T); \
				memmove(dest, dest + 1, count); \
				list->length--; \
				return 1; \
			} \
			else \
			{ \
				shouldRemove = 1; \
				a = (uint8_t*) &item; \
			} \
		} \
		return 0; \
	} \
	 \
	uint8_t removeAtWithDeleter_List_##T( \
		List_##T* list, \
		size_t index, \
		void* state, \
		void(*deleter)(void* state, T* item) \
	) \
	{ \
		if (index < list->length) \
		{ \
			T* dest = list->array + index; \
			deleter(state, dest); \
			size_t count = (list->capacity - index) * sizeof(T); \
			memmove(dest, dest + 1, count); \
			list->length--; \
			return 1; \
		} \
		return 0; \
	} \
	 \
	pair_size_t_uint8_t indexOf_List_##T(List_##T* list, T item) \
	{\
		uint8_t isMatch = 1; \
		uint8_t* a = (uint8_t*) &item; \
		uint8_t* b; \
		for (size_t i = 0; i < list->length; i++) \
		{ \
			b = (uint8_t*) (list->array + i); \
			for (size_t j = 0; j < sizeof(T); j++) \
			{ \
				isMatch &= *(a) == *(b); \
				a++; \
				b++; \
			} \
			if (isMatch) \
			{ \
				pair_size_t_uint8_t ret = { \
					.first = i, \
					.second = 1 \
				}; \
				return ret; \
			} \
			else \
			{ \
				isMatch = 1; \
				a = (uint8_t*) &item; \
			} \
		} \
		pair_size_t_uint8_t ret = { \
			.first = 0, \
			.second = 0 \
		}; \
		return ret; \
	} \
	 \
	pair_size_t_uint8_t lastIndexOf_List_##T(List_##T* list, T item) \
	{\
		uint8_t isMatch = 1; \
		uint8_t* a = (uint8_t*) &item; \
		uint8_t* b; \
		size_t index = 0; \
		size_t lastIndex = 0; \
		for (size_t i = 0; i < list->length; i--) \
		{ \
			index = lastIndex - i; \
			b = (uint8_t*) (list->array + index); \
			for (size_t j = 0; j < sizeof(T); j++) \
			{ \
				isMatch &= *(a) == *(b); \
				a++; \
				b++; \
			} \
			if (isMatch) \
			{ \
				pair_size_t_uint8_t ret = { \
					.first = index, \
					.second = 1 \
				}; \
				return ret; \
			} \
			else \
			{ \
				isMatch = 1; \
				a = (uint8_t*) &item; \
			} \
		} \
		pair_size_t_uint8_t ret = { \
			.first = 0, \
			.second = 0 \
		}; \
		return ret; \
	} \
	 \
	void clear_List_##T(List_##T* list) \
	{ \
		memset(list->array, 0, list->capacity * sizeof(T)); \
		list->length = 0; \
	} \
	 \
	void insert_List_##T(List_##T* list, size_t index, T item) \
	{ \
		size_t minLength = (list->length + 1); \
		while( \
			list->capacity < minLength & \
			list->capacity <= index) list->capacity *= 2; \
		list->array = list->realloc(list->array, list->capacity * sizeof(T)); \
		memmove( \
			list->array + index, \
			list->array + index + 1, \
			list->capacity - list->length \
		); \
		*(list->array + index) = item; \
	} \
	 \
	void insertRange_List_##T( \
		List_##T* list, \
		size_t index, \
		T* items, \
		size_t count \
	) \
	{ \
		while( \
			list->capacity < (list->length + count) & \
			list->capacity <= (index + count - 1)) list->capacity *= 2; \
		list->array = list->realloc(list->array, list->capacity * sizeof(T)); \
		memmove( \
			list->array + index, \
			list->array + index + count, \
			list->capacity - list->length \
		); \
		memmove( \
			list->array + index, \
			items, \
			count * sizeof(T) \
		); \
	} \
	 \
	void forEach_List_##T( \
		List_##T* list, \
		void* state, \
		void(*action)(void* state, T* item) \
	) \
	{ \
		T* endPtr = list->array + list->length; \
		for (T* p = list->array; p < endPtr; ++p) \
		{ \
			action(state, p); \
		} \
	}\
	 \
	void free_List_##T( \
		List_##T* list \
	) \
	{ \
		if (list->array) \
			list->free(list->array); \
		list->array = 0; \
	} \
	\
	void freeListWithDeleter_List_##T( \
		List_##T* list, \
		void* state, \
		void(*deleter)(void* state, T* item) \
	) \
	{ \
		T* endPtr = list->array + list->length; \
		for (T* p = list->array; p < endPtr; ++p) \
		{ \
			deleter(state, p); \
		} \
		if (list->array) \
			list->free(list->array); \
		list->array = 0; \
	} \
	 \
	void clearWithDeleter_List_##T( \
		List_##T* list, \
		void* state, \
		void(*deleter)(void* state, T* item) \
	) \
	{ \
		T* endPtr = list->array + list->length; \
		for (T* p = list->array; p < endPtr; ++p) \
		{ \
			deleter(state, p); \
		} \
		memset(list->array, 0, list->capacity * sizeof(T)); \
		list->length = 0; \
	} \
	 \
	uint8_t set_List_##T(List_##T* list, T item, size_t index) \
	{ \
		if (index < list->length) \
		{ \
			*(list->array + index) = item; \
			return 1; \
		} \
		return 0; \
	} \
	 \
	pair_##T##_uint8_t get_List_##T(List_##T* list, size_t index) \
	{ \
		pair_##T##_uint8_t ret = { 0 }; \
		if (index < list->length) \
		{ \
			ret.first = *(list->array + index); \
			ret.second = 1; \
		} \
		return ret; \
	} \
	 \
	pair_size_t_uint8_t getRef_List_##T(List_##T* list, size_t index) \
	{ \
		uint8_t inRange = index < list->length; \
		pair_size_t_uint8_t ret = { \
			.first = inRange * ((size_t) (list->array + index)), \
			.second = inRange \
		}; \
		return ret; \
	} \
	 \
	void sort_List_##T( \
		List_##T* list, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b) \
	) \
	{ \
		Heap_##T heap = { \
			.array = list->array, \
			.length = list->length, \
			.capacity = list->capacity, \
			.comparer = comparer, \
			.malloc = list->malloc, \
			.realloc = list->realloc, \
			.free = list->free, \
		}; \
		int64_t* endPtr = list->array + list->length; \
		heapify_Heap_##T(&heap); \
		T tmp; \
		size_t counter = 0; \
		while (heap.length) \
		{ \
			tmp = pop_Heap_##T(&heap); \
			*(list->array + heap.length) = tmp; \
		} \
		if (comparer(list->array, list->array + 1) > 0) \
			swap_##T(list->array, list->array + 1); \
	} \
	 \
	pair_size_t_uint8_t binarySearch_List_##T( \
		List_##T* list, \
		T item, \
		int8_t(*comparer)(const T* restrict a, const T* restrict b) \
	) \
	{ \
		size_t hi = list->length - 1; \
		size_t lo = 0; \
		size_t mid = 0; \
		pair_size_t_uint8_t ret = { 0 }; \
		int8_t cmp = 0; \
		while ((hi - lo) < list->length) \
		{ \
			mid = (hi + lo) / 2; \
			cmp = comparer(list->array + mid, &item); \
			if (cmp == 0) \
			{ \
				ret.first = mid; \
				ret.second = 1; \
				break; \
			} \
			if (cmp < 0) \
				lo = mid + 1; \
			else \
				hi = mid - 1; \
		} \
		return ret; \
	}
#endif
#endif //__LIST_H
