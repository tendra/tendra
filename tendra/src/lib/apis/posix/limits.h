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
+IMPLEMENT "ansi", "limits.h" ;

+DEFINE _POSIX_ARG_MAX 4096 ;
+DEFINE _POSIX_CHILD_MAX 6 ;
+DEFINE _POSIX_LINK_MAX 8 ;
+DEFINE _POSIX_MAX_CANON 255 ;
+DEFINE _POSIX_MAX_INPUT 255 ;
+DEFINE _POSIX_NAME_MAX 14 ;
+DEFINE _POSIX_NGROUPS_MAX 0 ;
+DEFINE _POSIX_OPEN_MAX 16 ;
+DEFINE _POSIX_PATH_MAX 255 ;
+DEFINE _POSIX_PIPE_BUF 512 ;

+CONST int NGROUPS_MAX ;

+IF 0
/* These values are optional */
+CONST int ARG_MAX, CHILD_MAX, LINK_MAX, MAX_CANON, MAX_INPUT ;
+CONST int NAME_MAX, OPEN_MAX, PATH_MAX, PIPE_BUF ;
+ENDIF
