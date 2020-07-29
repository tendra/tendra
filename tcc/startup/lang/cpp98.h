/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * STANDARD START-UP FILE FOR ISO C++
 *
 * This file defines the built-in operators used in ISO C++.
 */

#line 1 "<start-up>"
#pragma TenDRA begin

// LITERAL AND PROMOTION INFORMATION
#include "../literal/c89.h"
#ifdef __TCC_USHORT_TO_INT
#pragma promote unsigned short:int
#undef __TCC_USHORT_TO_INT
#endif

// BUILT-IN ALLOCATION FUNCTIONS
#pragma TenDRA keyword __size_t for keyword size_t
struct __bad_alloc {} ;	// will be replaced by std::bad_alloc
void *operator new ( __size_t ) throw ( __bad_alloc ) ;
void *operator new [] ( __size_t ) throw ( __bad_alloc ) ;
void operator delete ( void * ) throw () ;
void operator delete [] ( void * ) throw () ;

