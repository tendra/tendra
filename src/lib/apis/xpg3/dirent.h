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
+IMPLEMENT "posix", "dirent.h" ;
+USE "posix", "sys/types.h", "ino_t" ;

/* This type is abstracted */
+IF %% __STRICT_XPG3 %%
+TYPEDEF ino_t ~dirent_ino_t ;
+ELSE
+TYPE ( arith ) ~dirent_ino_t.1 ;
+MACRO ino_t __dirent_ino2ino ( ~dirent_ino_t ) ;
+MACRO ~dirent_ino_t __ino2dirent_ino ( ino_t ) ;
+IFNDEF ~building_libs
%%
#pragma accept conversion __dirent_ino2ino
#pragma accept conversion __ino2dirent_ino
%%
%%%
#include <dirent.h>
#define __dirent_ino2ino( X )	( ino_t ) ( X )
#define __ino2dirent_ino( X )	( __local_dirent_ino_t ) ( X )
%%%
+ENDIF
+ENDIF

+FIELD struct dirent {
    ~dirent_ino_t d_ino ;
} ;

+FUNC void seekdir ( DIR *, long ) ;
+FUNC long telldir ( DIR * ) ;
