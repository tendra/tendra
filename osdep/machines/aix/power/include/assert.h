/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include_next <assert.h>

#ifndef NDEBUG
#ifdef assert
#undef assert
#define assert(EX) ((EX) ? ((void)0) : _assert(# EX, __FILE__, __LINE__))
#endif
#endif
