#ifndef __BUILDING_LIBS


/*
    TOKEN DECLARATIONS

    The tokens __va_t, __va_start, va_arg and va_end are as in the
    ansi:stdarg header.  The only difference is that va_list is defined
    as its implementation type, rather than being a tokenised type.
*/

#pragma token TYPE __va_t # ~__va_t
#pragma token PROC ( EXP rvalue : __va_t : ) EXP rvalue : va_list : __va_start # ansi.stdarg.__va_start
#pragma token PROC ( EXP lvalue : va_list : e , TYPE t ) EXP rvalue : t : va_arg # ansi.stdarg.va_arg
#pragma token PROC ( EXP lvalue : va_list : ) EXP rvalue : void : va_end # ansi.stdarg.va_end
#pragma interface __va_t __va_start va_arg va_end


/*
    DEFINITION OF VA_START

    How va_start is defined in terms of __va_start depends on whether
    this is stdarg.h or varargs.h.
*/

#pragma TenDRA ident ... allow

#ifdef __HACKED_VARARGS_INCLUDED
#define va_alist		...
#define va_dcl
#define va_start( l )		( ( void ) ( l = __va_start ( ... ) ) )
#else
#define va_start( l, i )	( ( void ) ( l = __va_start ( ... ) ) )
#endif


#else

#endif
