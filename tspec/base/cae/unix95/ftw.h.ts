# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "cae/xsh4-base", "ftw.h.ts" ;
+IMPLEMENT "cae/unix95", "sys/stat.h.ts", "st_proto" ;

+CONST int FTW_PHYS, FTW_MOUNT, FTW_DEPTH, FTW_CHDIR ;
+CONST int FTW_SL, FTW_SLN ;

+FIELD struct FTW {
    int base ;
    int level ;
} ;

+FUNC int nftw ( const char *,
    int (*) ( const char *, const struct stat *, int, struct FTW * ),
    int, int ) ;
