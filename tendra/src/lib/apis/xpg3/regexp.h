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
/* This doesn't work properly at present */

+IFNDEF GETC
%% #error The macro GETC must be defined before regexp.h is included %%
+ENDIF
+IFNDEF PEEKC
%% #error The macro PEEKC must be defined before regexp.h is included %%
+ENDIF
+IFNDEF UNGETC
%% #error The macro UNGETC must be defined before regexp.h is included %%
+ENDIF
+IFNDEF RETURN
%% #error The macro RETURN must be defined before regexp.h is included %%
+ENDIF
+IFNDEF ERROR
%% #error The macro ERROR must be defined before regexp.h is included %%
+ENDIF
+IFNDEF INIT
%% #error The macro INIT must be defined before regexp.h is included %%
+ENDIF

+FUNC (extern) int advance ( const char *, const char * ) ;
+FUNC (extern) char *compile ( char *, char *, const char *, int ) ;
+FUNC (extern) int step ( const char *, const char * ) ;
+EXP (extern) char *loc1, *loc2, *locs ;
