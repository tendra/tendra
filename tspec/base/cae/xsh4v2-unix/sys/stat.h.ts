# $Id$

# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+USE "posix/posix", "sys/types.h.ts", "mode_t" ;
+USE "posix/posix", "sys/types.h.ts", "stat_t" ;

+SUBSET "st_proto" := {
    +IMPLEMENT "cae/xsh4-base", "sys/stat.h.ts" ;
    +IMPLEMENT "cae/xpg3", "sys/stat.h.ts", "s_isvtx" ;

    +FIELD struct stat {
        long st_blksize ;
        long st_blocks ;
    } ;

    +CONST int S_IFLNK ;

    +MACRO int S_ISLNK ( mode_t ) ;
} ;

+FUNC int fchmod ( int, mode_t ) ;
+FUNC int lstat ( const char *, struct stat * ) ;
+FUNC int mknod ( const char *, mode_t, dev_t ) ;

