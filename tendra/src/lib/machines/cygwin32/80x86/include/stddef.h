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
    REPLACEMENT STDDEF HEADER FOR linux/80x86

    The system does not provide stddef.h, GCC does.
    Provide a sensible definition.
*/

#ifndef __HACKED_LINUX_STDDEF_INCLUDED
#define __HACKED_LINUX_STDDEF_INCLUDED

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t ;
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef int ptrdiff_t ;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
typedef long int wchar_t ;
#endif

#ifndef NULL
#define NULL			0
#endif

#ifndef offsetof
#define offsetof( __S, __M )	( ( size_t ) &( ( ( __S * ) 0 )->__M ) )
#endif

#endif
