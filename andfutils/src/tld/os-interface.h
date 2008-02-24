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
 *	FS_FAST
 *
 * This should be defined if you want the program to use macros in place of
 * some function calls.  This will generally speed up the program (although
 * this is not guaranteed).  It also turns off the assertion checking
 * (unless ``FS_ASSERT'' is also defined).
 *
 *	FS_ASSERT
 *
 * This should be defined if you want assertion checking enabled.  This is on
 * by default, unless ``FS_FAST'' is defined, so it is only really useful to
 * define this if you have also defined ``FS_FAST'', but still want assertions
 * to be checked.  It is possible that less assertions will be checked, as
 * some of the "inlined" functions may have lost their assertions in the
 * macro version.
 *
 *	PO_CHAR_BIT
 *
 * This should be defined to be the number of bits in a ``char'' object, used
 * to define ``CHAR_BIT''.  In an ANSI C compliant standard library, this
 * macro is defined in <limits.h>. If the standard library is not ANSI
 * compliant and no value is provided, then ``8'' will be used.
 *
 *	PO_UINT_MAX
 *
 * This should be defined to be the maximum unsinged integer, and is used to
 * define ``UINT_MAX''.  In an ANSI C compliant standard library, this macro
 * is defined in <limits.h>. If the standard library is not ANSI compliant and
 * no value is provided, then ``(~(unsigned) 0)'' will be used.
 *
 *	PO_SEEK_SET
 *	PO_SEEK_CUR
 *	PO_SEEK_END
 *
 * These should be defined to be the values for ``SEEK_SET'', ``SEEK_CUR'' and
 * ``SEEK_END''.  In an ANSI C compliant standard library, they are defined in
 * <stdio.h>.  If the standard library is not ANSI compliant and no value is
 * provided, then ``0'', ``1'' and ``2'' will be used.
 *
 * This file also requires that one external function be provided:
 *
 *	void E_assertion_failed(char *, char *, unsigned)
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
 ** Type:	ByteT
 ** Type:	ByteT *
 ** Repr:	unsigned char
 *
 * This is the byte type.  It is possible that this could be larger than a
 * byte in some implementations.
 *
 ** Type:	BoolT
 ** Type:	BoolT *
 ** Repr:	int
 *
 * This is the boolean type.
 *
 ***=== CONSTANTS ============================================================
 *
 ** Constant:	TRUE
 ** Constant:	FALSE
 *
 * These expand to values suitable for the boolean constants true and false.
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
 ** Macro:	NIL(type)
 ** Exceptions:
 *
 * This is the null pointer macro.  The argument is the type for which a null
 * pointer is required.
 *
 ** Macro:	INLINE
 ** Exceptions:
 *
 * This macro may be used before a function to indicate that the function
 * should be inlined.  Normally it expands to nothing, however under the GNU C
 * compiler it expands to ``__inline__'' which causes the compiler to inline
 * the function.
 *
 ** Macro:	ASSERT (assertion)
 ** Exceptions:
 *
 * This macro causes the program to abort if the assertion provided does not
 * hold.  Assertion checking is disabled if the ``FS_FAST'' macro is defined
 * or if the ``FS_NO_ASSERT'' macro is defined.  The assertion "ASSERT
 * (FALSE);" is used to indicate that the program should never reach the
 * current line.
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

# ifdef FS_NO_FAST
#  undef FS_FAST
# endif /* defined (FS_NO_FAST) */
# ifndef FS_FAST
#  define FS_ASSERT
# endif /* !defined (FS_FAST) */
# ifdef FS_NO_ASSERT
#  undef FS_ASSERT
# endif /* defined (FS_NO_ASSERT) */

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

typedef unsigned char ByteT;
typedef int BoolT;

# define NIL(type) ((type) (0))

# define FALSE (0)
# define TRUE (1)

# ifdef __GNUC__
#  define INLINE __inline__
# else
#  define INLINE
# endif /* defined (__GNUC__) */

# ifdef FS_ASSERT
extern void			E_assertion_failed
	(char *, char *, unsigned);
#   define ASSERT(a) \
if (!(a)) { \
    E_assertion_failed (#a, __FILE__, (unsigned) __LINE__); \
    abort (); \
}
# else
#  define ASSERT(a)
# endif /* defined (FS_ASSERT) */

# ifdef __TenDRA__
#  pragma TenDRA keyword EXHAUSTIVE for exhaustive
#  pragma TenDRA keyword FALL_THROUGH for fall into case
#  pragma TenDRA keyword UNREACHED for set unreachable
# else
#  define EXHAUSTIVE
#  define FALL_THROUGH
#  define UNREACHED ASSERT (FALSE)
# endif /* defined (__TenDRA__) */

#  ifndef CHAR_BIT
#   ifdef PO_CHAR_BIT
#    define CHAR_BIT PO_CHAR_BIT
#   else
#    define CHAR_BIT 8
#   endif /* defined (PO_CHAR_BIT) */
#  endif /* !defined (CHAR_BIT) */

#  ifndef UINT_MAX
#   ifdef PO_UINT_MAX
#    define UINT_MAX PO_UINT_MAX
#   else
#    define UINT_MAX (~(unsigned) 0)
#   endif /* defined (PO_UINT_MAX) */
#  endif /* !defined (UINT_MAX) */

#  ifndef SEEK_SET
#   ifdef PO_SEEK_SET
#    define SEEK_SET PO_SEEK_SET
#   else
#    define SEEK_SET (0)
#   endif /* defined (PO_SEEK_SET) */
#  endif /* !defined (SEEK_SET) */

#  ifndef SEEK_CUR
#   ifdef PO_SEEK_CUR
#    define SEEK_CUR PO_SEEK_CUR
#   else
#    define SEEK_CUR (1)
#   endif /* defined (PO_SEEK_CUR) */
#  endif /* !defined (SEEK_CUR) */

#  ifndef SEEK_END
#   ifdef PO_SEEK_END
#    define SEEK_END PO_SEEK_END
#   else
#    define SEEK_END (2)
#   endif /* defined (PO_SEEK_END) */
#  endif /* !defined (SEEK_END) */

#endif /* !defined (H_OS_INTERFACE) */
