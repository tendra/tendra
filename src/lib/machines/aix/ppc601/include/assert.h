#include_next <assert.h>

#ifndef NDEBUG
#ifdef assert
#undef assert
#define assert(EX) ((EX) ? ((void)0) : _assert(# EX, __FILE__, __LINE__))
#endif
#endif
