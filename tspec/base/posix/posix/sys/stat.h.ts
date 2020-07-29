# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "posix/posix", "sys/types.h.ts" ;
+USE "c/c89", "time.h.ts", "time_t" (!?) ;

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
    nlink_t st_nlink ;
    uid_t st_uid ;
    gid_t st_gid ;
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
+FUNC int chmod ( const char *, mode_t ) ;
+FUNC int mkdir ( const char *, mode_t ) ;
+FUNC int mkfifo ( const char *, mode_t ) ;
+FUNC mode_t umask ( mode_t ) ;
