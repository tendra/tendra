/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
    STANDARD STRING FUNCTION DEFINITIONS

    These routines define the standard C string functions which C++
    overloads.  They are defined in terms of the C versions.
*/

#include <cstddef>
using namespace std ;

extern "C" {
    // Declare the C versions
    char *strchr ( const char *, int ) ;
    char *strrchr ( const char *, int ) ;
    char *strpbrk ( const char *, const char * ) ;
    char *strstr ( const char *, const char * ) ;
    void *memchr ( const void *, int, size_t ) ;
}

namespace std {
    char *strchr ( char *s, int c )
    {
	return ( ::strchr ( s, c ) ) ;
    }

    const char *strchr ( const char *s, int c )
    {
	return ( ( const char * ) ::strchr ( s, c ) ) ;
    }

    char *strrchr ( char *s, int c )
    {
	return ( ::strrchr ( s, c ) ) ;
    }

    const char *strrchr ( const char *s, int c )
    {
	return ( ( const char * ) ::strrchr ( s, c ) ) ;
    }

    char *strpbrk ( char *s, const char *t )
    {
	return ( ::strpbrk ( s, t ) ) ;
    }

    const char *strpbrk ( const char *s, const char *t )
    {
	return ( ( const char * ) ::strpbrk ( s, t ) ) ;
    }

    char *strstr ( char *s, const char *t )
    {
	return ( ::strstr ( s, t ) ) ;
    }

    const char *strstr ( const char *s, const char *t )
    {
	return ( ( const char * ) ::strstr ( s, t ) ) ;
    }

    void *memchr ( void *s, int c, size_t n )
    {
	return ( ::memchr ( s, c, n ) ) ;
    }

    const void *memchr ( const void *s, int c, size_t n )
    {
	return ( ( const void * ) ::memchr ( s, c, n ) ) ;
    }
}
