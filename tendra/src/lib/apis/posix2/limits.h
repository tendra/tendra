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
+IMPLEMENT "posix1", "limits.h" ;

+CONST int BC_BASE_MAX, BC_DIM_MAX, BC_SCALE_MAX, BC_STRING_MAX ;
+CONST int COLL_WEIGHTS_MAX, EXPR_NEST_MAX, LINE_MAX, RE_DUP_MAX ;
+CONST int _POSIX2_BC_BASE_MAX, _POSIX2_BC_DIM_MAX, _POSIX2_BC_SCALE_MAX ;
+CONST int _POSIX2_BC_STRING_MAX, _POSIX2_COLL_WEIGHTS_MAX ;
+CONST int _POSIX2_EXPR_NEST_MAX, _POSIX2_LINE_MAX, _POSIX2_RE_DUP_MAX ;
