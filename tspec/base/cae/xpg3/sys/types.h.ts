# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix/posix", "sys/types.h.ts" ;
+IMPLEMENT "c/c89", "time.h.ts", "clock_t" (!?) ;
+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" (!?) ;
+IMPLEMENT "c/c89", "time.h.ts", "time_t" (!?) ;

# ftok() key_t result comparable with (key_t)-1, so not opaque
+SUBSET "key_t" := { +TYPE ( int ) key_t ; } ;

+IF 0
/* caddr_t is optional in XPG3 */
+SUBSET "caddr_t" := {
    +IFNDEF ~building_libs
    /* caddr_t is meant to be a generic pointer */
    +TYPEDEF void *caddr_t ;
    +ELSE
%%
#ifdef __CADDR_TYPE__
typedef __CADDR_TYPE caddr_t ;
#else
typedef char *caddr_t ;
#endif
%%
    +ENDIF
} ;
/* addr_t is optional in XPG3 */
+ENDIF
