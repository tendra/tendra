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
 * This file (and others in this directory) makes use of several macros to
 * turn on certain features.  These macros are listed below.  In each case
 * there is a macro that begins with ``FS_NO_'' instead of ``FS_'' that turns
 * the feature off; if both are defined, the ``FS_NO_'' macro takes
 * precedence, and the feature is turned off.
 *
 ***=== FROM ANSI ============================================================
 *
 * The following ANSI C functions are declared:
 *
 *	NoReturnT			abort
 *			(void)
 *	void *			calloc
 *			(SizeT length, SizeT size)
 *	void *			malloc
 *			(SizeT size)
 *	NoReturnT			exit
 *			(int exit_code)
 *	void				free
 *			(void * pointer)
 *	char *			getenv
 *			(char * name)
 *	int				memcmp
 *			(void * ptr1, void * ptr2, SizeT length)
 *	void *			memcpy
 *			(void * to, void * from, SizeT length)
 *	void *			memset
 *			(void * ptr, int val, SizeT length)
 *	void *			memchr
 *			(void * ptr, int val, SizeT length)
 *	SizeT				strlen
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
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	int			mkdir
 *			(char * path, int mode)
 ** Exceptions:
 *
 * This function is only declared if the ``FS_MKDIR'' macro is defined.  This
 * macro should also be tested before the function is used anywhere.  It is
 * the POSIX directory creation function.
 *
 ** Function:	char *		strerror
 *			(int error)
 ** Exceptions:
 *
 * This function is only declared if the ``FS_STRERROR'' macro is defined.
 * This macro should also be tested before the function is used anywhere.  It
 * is the ANSI function for obtaining a textual description of a system error
 * message.
 *
 ***=== VARIABLES ============================================================
 *
 ** Variable:	int			sys_nerr
 *
 * This variable is only declared if the ``FS_SYS_ERRLIST'' macro is defined.
 * It contains the number of error messages stored in the ``sys_errlist''
 * vector.
 *
 ** Variable:	char *		sys_errlist []
 *
 * This variable is only declared if the ``FS_SYS_ERRLIST'' macro is defined.
 * It contains the text of the system error messages.
 *
 ** Variable:	int			errno
 *
 * This variable contains the number of the current system error.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	NoReturnT
 ** Repr:	void
 *
 * This is the return type of a function that doesn't return (e.g.
 * ``longjmp'').  Normally this is just ``void'', however the GNU C compiler
 * can produce better code if this is declared as ``__volatile__ void''.  The
 * TenDRA compiler can be told that a function doesn't return as well.
 *
 ** Type:	SizeT
 ** Type:	SizeT *
 ** Repr:	size_t
 *
 * This is the type of the return value of the "sizeof" operator.
 *
 ***=== CONSTANTS ============================================================
 *
 ** Constant:	TRUE
 ** Constant:	FALSE
 *
 * These expand to values suitable for the boolean constants true and false.
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
 ** Macro:	FS_BINARY_STDIO
 ** Exceptions:
 *
 * This macro is defined if ANSI binary input and output is supported
 * (i.e. the "b" modifier is allowed in the second argument to ``fopen'').
 *
 ** Macro:	FS_STRERROR
 ** Exceptions:
 *
 * This macro is defined if the ANSI function ``strerror'' is defined.
 *
 ** Macro:	FS_SYS_ERRLIST
 ** Exceptions:
 *
 * This macro is defined if the BSD ``sys_nerr'' and ``sys_errlist'' variables
 * are defined.  If ``FS_STRERROR'' is defined, then the ``strerror'' function
 * should be used in preference to ``sys_nerr'' and ``sys_errlist''.
 *
 ** Macro:	FS_MKDIR
 ** Exceptions:
 *
 * This macro is defined if the POSIX function ``mkdir'' is defined.
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
 */

#ifndef H_OS_INTERFACE
#define H_OS_INTERFACE

# ifdef __TenDRA__
#  pragma TenDRA keyword UNUSED for discard variable
# else
#  define UNUSED(v)
# endif /* defined (__TenDRA__) */

# ifdef __TenDRA__
#  pragma TenDRA keyword EXHAUSTIVE for exhaustive
#  pragma TenDRA keyword FALL_THROUGH for fall into case
#  pragma TenDRA keyword UNREACHED for set unreachable
# else
#  define EXHAUSTIVE
#  define FALL_THROUGH
#  include <assert.h>
#  define UNREACHED assert(FALSE)
# endif /* defined (__TenDRA__) */

#endif /* !defined (H_OS_INTERFACE) */
