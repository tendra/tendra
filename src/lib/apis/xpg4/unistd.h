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
+USE "xpg4", "sys/types.h" (!?) ;
+IMPLEMENT "posix2", "unistd.h" ;
+IMPLEMENT "xpg3", "unistd.h", "u_plus" ;

+IFNDEF _XOPEN_VERSION
+DEFINE _XOPEN_VERSION.1	4 ;
+ENDIF

+FUNC void swab ( const void *, void *, ssize_t ) ;	# different

+CONST int _POSIX2_VERSION, _SC_2_C_BIND, _SC_2_C_VERSION, _SC_2_UPE ;
+CONST int _XOPEN_XCU_VERSION, _SC_XOPEN_CRYPT, _SC_XOPEN_ENH_I18N ;
+CONST int _SC_XOPEN_SHM ;
