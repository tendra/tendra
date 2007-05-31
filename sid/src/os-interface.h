/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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
 * os-interface.h - Primitive definitions.
 *
 * This file specifies an interface to the host system's C library, compiler
 * and operating system.  It provides definitions of basic types, constants
 * and macros, and declarations of functions, that can be used by other
 * components of the program.
 *
 * This file used to provide portability abstractions; now all that remains
 * are definitions for semantic purposes, such as CmpT.
 */

#ifndef H_OS_INTERFACE
#define H_OS_INTERFACE

# ifdef __GNUC__
typedef void NoReturnT;
# else
#  ifdef __TenDRA__
#   pragma TenDRA type NoReturnT for bottom
#  else

/*
 * This is the return type of a function that doesn't return (e.g.
 * ``longjmp'').  Normally this is just ``void'', however the GNU C compiler
 * can produce better code if this is declared as ``__volatile__ void''.  The
 * TenDRA compiler can be told that a function doesn't return as well.
 */
#   define NoReturnT void

#  endif /* defined (__TenDRA__) */
# endif /* defined (__GNUC__) */

# ifdef __TenDRA__
#  pragma TenDRA keyword UNUSED for discard variable
#  pragma TenDRA keyword KW_WEAK_PROTOTYPE for weak
# else

/*
 * This macro documents the fact that the specified variable will no longer be
 * used.  One use is to indicate function parameters that are not used.  On
 * most compilers it will do nothing, but on compilers that support it it will
 * tell the compiler that the variable is not expected to be used.
 */
#  define UNUSED(v)
#  define KW_WEAK_PROTOTYPE
# endif /* defined (__TenDRA__) */

/*
 * This is the byte type.  It is possible that this could be larger than an
 * octet in some implementations.
 */
typedef unsigned char ByteT;

/*
 * This is the boolean type.
 */
typedef int BoolT;

/*
 * This is the type returned by comparison functions.  The values represent
 * the fact that the first argument is less than, equal to, or greater than
 * the second argument respectively.
 */
typedef enum {
    CMP_LT,
    CMP_EQ,
    CMP_GT
} CmpT;

/*
 * These expand to values suitable for the boolean constants true and false.
 * Eventually these will be replaced with C99's stdbool.h along with the
 * BoolT type.
 */
# define FALSE (0)
# define TRUE (1)

# ifdef __TenDRA__
#  pragma TenDRA keyword EXHAUSTIVE for exhaustive
#  pragma TenDRA keyword FALL_THROUGH for fall into case
#  pragma TenDRA keyword UNREACHED for set unreachable
# else
#  include <stdlib.h>
#  include <assert.h>

/*
 * This macro documents the fact that the switch statement in which it appears
 * is meant to be exhaustive.  It is used as follows:
 *
 *	switch (expression) EXHAUSTIVE { ... }
 */
#  define EXHAUSTIVE

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
#  define FALL_THROUGH

/*
 * This macro documents the fact that the location that it occurs in should be
 * unreachable.
 */
#  define UNREACHED assert(!"UNREACHED"); abort();
# endif /* defined (__TenDRA__) */

#endif /* !defined (H_OS_INTERFACE) */
