#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
+IMPLEMENT "posix", "sys/types.h" ;
+IMPLEMENT "ansi", "time.h", "clock_t" (!?) ;
+IMPLEMENT "ansi", "stddef.h", "size_t" (!?) ;
+IMPLEMENT "ansi", "time.h", "time_t" (!?) ;

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
