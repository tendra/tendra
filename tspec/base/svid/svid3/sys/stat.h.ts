# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "cae/xpg3", "sys/stat.h.ts", "st_proto" ;
+IMPLEMENT "cae/xpg3", "sys/stat.h.ts", "s_isvtx" ;

+FIELD struct stat {
    long st_blksize ;
    long st_blocks ;
} ;

+CONST int S_IFLNK ;

+FUNC int lstat ( const char *, struct stat * ) ;
+FUNC int mknod ( const char *, mode_t, dev_t ) ;
+FUNC int fchmod ( int, mode_t ) ;
