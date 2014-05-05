# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix", "sys/types.h.ts", "stat_t" ;
+IMPLEMENT "c/c89", "time.h.ts", "time_t" ;

+SUBSET "st_proto" := {
    +IMPLEMENT "xpg4", "sys/stat.h.ts" ;
    +IMPLEMENT "xpg3", "sys/stat.h.ts", "s_isvtx" ;

    +FIELD struct stat {
	long st_blksize ;
	long st_blocks ;
    } ;

    +CONST int S_IFLNK ;

    +MACRO int S_ISLNK ( mode_t ) ;

    # CAE, Networking Services, Issue 4
    +CONST int S_IFSOCK ;

    +MACRO int S_ISSOCK ( mode_t ) ;
} ;

+FUNC int fchmod ( int, mode_t ) ;
+FUNC int lstat ( const char *, struct stat * ) ;
+FUNC int mknod ( const char *, mode_t, dev_t ) ;
