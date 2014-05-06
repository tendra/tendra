# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix", "dirent.h.ts" ;
+USE "posix", "sys/types.h.ts", "ino_t" ;

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
