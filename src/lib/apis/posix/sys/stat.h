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
+USE "posix", "sys/types.h" ;
+USE "ansi", "time.h", "time_t" (!?) ;

/* This type is abstracted */
+IF %% __STRICT_POSIX %%
+TYPEDEF mode_t ~stat_mode_t ;
+ELSE
+TYPE ( arith ) ~stat_mode_t.1 ;
+MACRO mode_t __stat_mode2mode ( ~stat_mode_t ) ;
+MACRO ~stat_mode_t __mode2stat_mode ( mode_t ) ;
+IFNDEF ~building_libs
%%
#pragma accept conversion __stat_mode2mode
#pragma accept conversion __mode2stat_mode
%%
%%%
#include <sys/stat.h>
#define __stat_mode2mode( X )	( mode_t ) ( X )
#define __mode2stat_mode( X )	( __local_stat_mode_t ) ( X )
%%%
+ENDIF
+ENDIF

+FIELD struct stat | struct_stat {
    dev_t st_dev ;
    ino_t st_ino ;
    ~stat_mode_t st_mode ;
    short st_nlink ;
    uid_t st_uid ;
    short st_gid ;
    off_t st_size ;
    time_t st_atime ;
    time_t st_mtime ;
    time_t st_ctime ;
} ;

+CONST int S_IRWXU, S_IRUSR, S_IWUSR, S_IXUSR, S_IRWXG, S_IRGRP, S_IWGRP ;
+CONST int S_IXGRP, S_IRWXO, S_IROTH, S_IWOTH, S_IXOTH, S_ISUID, S_ISGID ;

+MACRO int S_ISBLK ( mode_t ) ;
+MACRO int S_ISCHR ( mode_t ) ;
+MACRO int S_ISDIR ( mode_t ) ;
+MACRO int S_ISFIFO ( mode_t ) ;
+MACRO int S_ISREG ( mode_t ) ;

+FUNC int fstat ( int, struct stat * ) ;
+FUNC int stat ( const char *, struct stat * ) ;
+FUNC int chmod ( const char *, int ) ;
+FUNC int mkdir ( const char *, int ) ;
+FUNC int mkfifo ( const char *, int ) ;
+FUNC mode_t umask ( int ) ;
