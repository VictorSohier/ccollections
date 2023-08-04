#include <stddef.h>

#ifndef __PAIR_H
#define __PAIR_H

#ifndef define_pair
#define define_pair(T1, T2) \
	typedef struct { \
		T1 first; \
		T2 second; \
	} pair_##T1##_##T2;
#endif

#endif
