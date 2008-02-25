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
 * check.h - Primitive definitions common to several interfaces.
 *
 * This file specifies an interface to the host system's compiler for
 * compiler-specific features related to checking.
 */

#ifndef CHECK_INCLUDED
#define CHECK_INCLUDED

/*
 * This is the return type of a function that doesn't return (e.g.
 * ``longjmp'').
 */
# if defined __TenDRA__
#  pragma TenDRA type NORETURN for bottom
# elif defined __GNUC__
#  define NORETURN __attribute__((noreturn)) void
# else
#  define NORETURN void
# endif

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
#  include <stdlib.h>
#  define UNREACHED do { assert(!"unreachable"); abort(); } while (0)
# endif /* defined (__TenDRA__) */

/*
 * This macro documents the fact that the switch statement in which it appears
 * is meant to be exhaustive.  It is used as follows:
 *
 *  switch (expression) EXHAUSTIVE { ... }
 */
# ifdef __TenDRA__
#  pragma TenDRA keyword EXHAUSTIVE for exhaustive
# else
#  define EXHAUSTIVE
# endif

/*
 * A weak prototype contains function parameter type information, but has none
 * of the automatic argument conversions associated with a normal prototype.
 * Instead weak prototypes imply the usual argument promotion passing rules for
 * non-prototyped functions.
 */
# ifdef __TenDRA__
#  pragma TenDRA keyword WEAK for weak
# else
#  define WEAK
# endif

#endif /* CHECK_INCLUDED */
