/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
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
