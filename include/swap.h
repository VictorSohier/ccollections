#ifndef __SWAP_H
#define __SWAP_H
#ifndef define_swap
#define define_swap(T) \
	void swap_##T(T* a, T* b)\
	{ \
		T tmp = *a; \
		*a = *b; \
		*b = tmp; \
	}
#endif
#endif
