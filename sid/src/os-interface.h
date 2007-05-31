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


/**** os-interface.h --- Primitive definitions.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies an interface to the host system's C library, compiler
 * and operating system.  It provides definitions of basic types, constants
 * and macros, and declarations of functions, that can be used by other
 * components of the program.
 *
 * This file (and others in this directory) makes use of several macros to
 * turn on certain features.  These macros are listed below.  In each case
 * there is a macro that begins with ``FS_NO_'' instead of ``FS_'' that turns
 * the feature off; if both are defined, the ``FS_NO_'' macro takes
 * precedence, and the feature is turned off.  In addition, the ``FS_NO_STDC''
 * macro may be used to turn off the ``__STDC__'' macro (in the cases where
 * the system isn't really ANSI compliant), and the ``FS_NO_FILE_INFO'' macro
 * should be defined if the ``__FILE__'' or ``__LINE__'' macros are
 * unsupported.
 *
 * As well as the feature switch macros, there are some portability option
 * macros as well.  These provide values for types and constants when the type
 * cannot be otherwise deduced.  These macros are ignored when the correct
 * value can be obtained automatically (this generally means on an ANSI
 * compliant system).
 *
 * This file also requires that one external function be provided:
 *
 *	void				E_assertion_failed
 *			(char *, char *, unsigned)
 *
 * This function will be called if an assertion fails.  It will be called with
 * the text of the assertion, the name of the file in which the assertion was
 * written, and line on which it occured.
 *
 ***=== FROM ANSI ============================================================
 *
 * The following ANSI C functions are declared:
 *
 *	NoReturnT			abort
 *			(void)
 *	void *			calloc
 *			(size_t length, size_t size)
 *	void *			malloc
 *			((size_t size)
 *	NoReturnT			exit
 *			(int exit_code)
 *	void				free
 *			(void * pointer)
 *	char *			getenv
 *			(char * name)
 *	int				memcmp
 *			(void * ptr1, void * ptr2, size_t length)
 *	void *			memcpy
 *			(void * to, void * from, size_t length)
 *	void *			memset
 *			(void * ptr, int val, size_t length)
 *	void *			memchr
 *			(void * ptr, int val, size_t length)
 *	size_t				strlen
 *			(char * string)
 *	int				strcmp
 *			(char * string1, char * string2)
 *	char *			strcpy
 *			(char * to, char * from)
 *	char *			strchr
 *			(char * string, int c)
 *	char *			strrchr
 *			(char * string, int c)
 *
 * Also everything in <setjmp.h> and <stdio.h> is included (hopefully this is
 * sufficiently common to be used even on non-ANSI platforms).  Where features
 * are absent on non-ANSI systems, support for them will need to be added.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	void *
 ** Repr:	void *
 *
 * This is the generic pointer type.  It can be used to store a pointer to any
 * non-function object.
 *
 ** Type:	NoReturnT
 ** Repr:	void
 *
 * This is the return type of a function that doesn't return (e.g.
 * ``longjmp'').  Normally this is just ``void'', however the GNU C compiler
 * can produce better code if this is declared as ``__volatile__ void''.  The
 * TenDRA compiler can be told that a function doesn't return as well.
 *
 ** Type:	size_t
 ** Type:	size_t *
 ** Repr:	size_t
 *
 * This is the type of the return value of the "sizeof" operator.
 *
 ** Type:	ByteT
 ** Type:	ByteP
 ** Repr:	unsigned char
 *
 * This is the byte type.  It is possible that this could be larger than a
 * byte in some implementations.
 *
 ** Type:	BoolT
 ** Type:	BoolP
 ** Repr:	int
 *
 * This is the boolean type.
 *
 ** Type:	CmpT
 ** Type:	CmpP
 ** Repr:	enum {CMP_LT, CMP_EQ, CMP_GT}
 *
 * This is the type returned by comparison functions.  The values represent
 * the fact that the first argument is less than, equal to, or greater than
 * the second argument respectively.
 *
 ***=== CONSTANTS ============================================================
 *
 ** Constant:	TRUE
 ** Constant:	FALSE
 *
 * These expand to values suitable for the boolean constants true and false.
 *
 ** Constant:	EXIT_SUCCESS
 ** Constant:	EXIT_FAILURE
 *
 * These values should be used as arguments to the ``exit'' function to
 * indicate success or failure of the program.
 *
 ** Constant:	UINT_MAX
 *
 * This is the maximum unsigned integer value.
 *
 ** Constant:	CHAR_BIT
 *
 * This is the number of bits in a ``char'' object.
 *
 ***=== MACROS ===============================================================
 *
 ** Macro:	FS_NO_FILE_INFO
 ** Exceptions:
 *
 * This macro is defined if ``__FILE__'' or ``__LINE__'' are unsupported.
 * They will be defined as macros with some default value in this case, but
 * the programmer may wish to do something different.
 *
 ** Macro:	UNUSED (variable)
 ** Exceptions:
 *
 * This macro documents the fact that the specified variable will no longer be
 * used.  One use is to indicate function parameters that are not used.  On
 * most compilers it will do nothing, but on compilers that support it it will
 * tell the compiler that the variable is not expected to be used.
 *
 ** Macro:	EXHAUSTIVE
 ** Exceptions:
 *
 * This macro documents the fact that the switch statement in which it appears
 * is meant to be exhaustive.  It is used as follows:
 *
 *	switch (expression) EXHAUSTIVE { ... }
 *
 ** Macro:	UNREACHED
 ** Exceptions:
 *
 * This macro documents the fact that the location that it occurs in should be
 * unreachable.
 *
 ** Macro:	FALL_THROUGH
 ** Exceptions:
 *
 * This macro documents the fact that the current case of a switch statement
 * should follow through into the next (immediately following) case.  It is
 * used as follows:
 *
 *	case 1:
 *	  ...
 *	  FALL_THROUGH;
 *	case 2:
 *	  ...
 *
 **** Change Log:
 * $Log: os-interface.h,v $
 * Revision 1.3  1998/03/16  11:26:35  release
 * Modifications prior to version 4.1.2.
 *
 * Revision 1.2  1998/02/04  10:46:57  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/08  16:11:39  smf
 * Put braces into union initialisation macros (as per ANSI spec).
 * Guarded "gcc" builtin functions.
 *
 * Revision 1.2  1994/12/12  11:45:45  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:11  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#ifndef H_OS_INTERFACE
#define H_OS_INTERFACE

# ifdef __GNUC__
typedef void NoReturnT;
# else
#  ifdef __TenDRA__
#   pragma TenDRA type NoReturnT for bottom
#  else
#   define NoReturnT void
#  endif /* defined (__TenDRA__) */
# endif /* defined (__GNUC__) */

# ifdef __TenDRA__
#  pragma TenDRA keyword UNUSED for discard variable
# else
#  define UNUSED(v)
# endif /* defined (__TenDRA__) */

typedef unsigned char ByteT, *ByteP;
typedef int BoolT, *BoolP;
typedef enum {
    CMP_LT,
    CMP_EQ,
    CMP_GT
} CmpT, *CmpP;

# define FALSE (0)
# define TRUE (1)

# ifdef __TenDRA__
#  pragma TenDRA keyword EXHAUSTIVE for exhaustive
#  pragma TenDRA keyword FALL_THROUGH for fall into case
#  pragma TenDRA keyword UNREACHED for set unreachable
# else
#  include <stdlib.h>
#  include <assert.h>
#  define EXHAUSTIVE
#  define FALL_THROUGH
#  define UNREACHED assert(!"UNREACHED"); abort();
# endif /* defined (__TenDRA__) */

#endif /* !defined (H_OS_INTERFACE) */
