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
    STANDARD WIDE STRING FUNCTION DEFINITIONS

    These routines define the standard C wide string functions which C++
    overloads.
*/

#include <cstddef>
using namespace std ;

extern "C" {
    // Declare the C versions
    wchar_t *wcschr ( const wchar_t *, wchar_t ) ;
    wchar_t *wcsrchr ( const wchar_t *, wchar_t ) ;
    wchar_t *wcspbrk ( const wchar_t *, const wchar_t * ) ;
    wchar_t *wcsstr ( const wchar_t *, const wchar_t * ) ;
    wchar_t *wmemchr ( const wchar_t *, wchar_t, size_t ) ;
}

namespace std {
    wchar_t *wcschr ( wchar_t *s, wchar_t c )
    {
	return ( ::wcschr ( s, c ) ) ;
    }

    const wchar_t *wcschr ( const wchar_t *s, wchar_t c )
    {
	return ( ( const wchar_t * ) ::wcschr ( s, c ) ) ;
    }

    wchar_t *wcsrchr ( wchar_t *s, wchar_t c )
    {
	return ( ::wcsrchr ( s, c ) ) ;
    }

    const wchar_t *wcsrchr ( const wchar_t *s, wchar_t c )
    {
	return ( ( const wchar_t * ) ::wcsrchr ( s, c ) ) ;
    }

    wchar_t *wcspbrk ( wchar_t *s, const wchar_t *t )
    {
	return ( ::wcspbrk ( s, t ) ) ;
    }

    const wchar_t *wcspbrk ( const wchar_t *s, const wchar_t *t )
    {
	return ( ( const wchar_t * ) ::wcspbrk ( s, t ) ) ;
    }

    wchar_t *wcsstr ( wchar_t *s, const wchar_t *t )
    {
	return ( ::wcsstr ( s, t ) ) ;
    }

    const wchar_t *wcsstr ( const wchar_t *s, const wchar_t *t )
    {
	return ( ( const wchar_t * ) ::wcsstr ( s, t ) ) ;
    }

    wchar_t *wmemchr ( wchar_t *s, wchar_t c, size_t n )
    {
	return ( ::wmemchr ( s, c, n ) ) ;
    }

    const wchar_t *wmemchr ( const wchar_t *s, wchar_t c, size_t n )
    {
	return ( ( const wchar_t * ) ::wmemchr ( s, c, n ) ) ;
    }
}
