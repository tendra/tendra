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
    SYSTEM START-UP FILE FOR linux/80x86

    This file defines any built-in macros etc. necessary to traverse the
    system headers correctly.
*/

#ifndef __TDF_SYS_INCLUDED
#define __TDF_SYS_INCLUDED

#include <Xsystem>

#pragma TenDRA begin
#pragma TenDRA set size_t : unsigned int
#pragma TenDRA set wchar_t : long int
#pragma TenDRA set ptrdiff_t : int
#pragma TenDRA character signed
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA longlong type allow

/* Put target-dependent macro definitions here */

#ifndef __NO_BUILTIN_ASSERTIONS
#assert machine(i386)
#assert cpu(i386)
#assert system(unix)
#assert system(winnt)
#unassert lint
#endif

#define i386		1
#define __i386		1
#define __i386__	1
#define _X86_		1
#define _WIN32		1
#define __CYGWIN32__	1
#define __WINNT		1

/* macros to match GNU C extensions used in headers */
#ifndef __inline__
#pragma TenDRA keyword __inline__ for inline
#endif

#ifndef __signed__
#define __signed__	signed
#endif

#ifndef __attribute__
#define __attribute__(p)
#endif

/* gcc has alloca builtin */
#include <alloca.h>

#endif
