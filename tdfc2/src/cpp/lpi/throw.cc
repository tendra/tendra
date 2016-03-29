/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#pragma implement interface "longjump.h"

#include "implement.h"

#pragma implement interface "throw.h"

#include <exception>

using namespace std;


/*
 * IMPLEMENTATION OF EXCEPTION HANDLING INTERFACE
 *
 * These declarations and macro definitions give the implementation of
 * the exception handling tokens declared in throw.h.
 */

#define throw_exception(X, Y, Z) \
	(__TCPPLUS_throw((X), (Y), (Z)))

#define rethrow_exception() (__TCPPLUS_throw(NULL, NULL, NULL))
#define catch_exception(X)  (__TCPPLUS_catch((X)))
#define alloc_exception(X)  (__TCPPLUS_alloc_except((X)))
#define value_exception     (__TCPPLUS_except.value[1])
#define caught_exception()  (__TCPPLUS_except.unwinding = false)
#define end_exception()     (__TCPPLUS_handled())
#define ill_exception(X)    (__TCPPLUS_unexpected((X)))

typedef EXCEPTION exception_type;

#define try_begin(X, Y, Z)                     \
    {                                          \
        (X)->frame = (Y);                      \
        (X)->label = (Z);                      \
        (X)->dtors = NULL;                     \
        (X)->next  = __TCPPLUS_except.buf [0]; \
        __TCPPLUS_except.buf[0] = (X);         \
    }

#define try_end(X)                             \
    {                                          \
        __TCPPLUS_except.buf[0] = (X)->next;   \
    }

