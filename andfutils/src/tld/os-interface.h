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
 * os-interface.h - Primitive interfaces.
 *
 * This file specifies an interface to the host system's C compiler, for
 * compiler-specific features.
 */

#ifndef H_OS_INTERFACE
#define H_OS_INTERFACE

/*
 * This macro documents the fact that the specified variable will no longer be
 * used.  One use is to indicate function parameters that are not used.  On
 * most compilers it will do nothing, but on compilers that support it it will
 * tell the compiler that the variable is not expected to be used.
 */
# ifdef __TenDRA__
#  pragma TenDRA keyword UNUSED for discard variable
# else
#  define UNUSED(v)
# endif /* defined (__TenDRA__) */

/*
 * This macro documents the fact that the current case of a switch statement
 * should follow through into the next (immediately following) case.  It is
 * used as follows:
 *
 *	case 1:
 *	  ...
 *	  FALL_THROUGH;
 *	case 2:
 *	  ...
 */
# ifdef __TenDRA__
#  pragma TenDRA keyword FALL_THROUGH for fall into case
# else
#  define FALL_THROUGH
# endif /* defined (__TenDRA__) */

/*
 * This macro documents the fact that the location that it occurs in should be
 * unreachable.
 */
# ifdef __TenDRA__
#  pragma TenDRA keyword UNREACHED for set unreachable
# else
#  include <assert.h>
#  define UNREACHED assert(FALSE)
# endif /* defined (__TenDRA__) */

#endif /* !defined (H_OS_INTERFACE) */
