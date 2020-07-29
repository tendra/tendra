# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "cae/xpg3", "ftw.h.ts" ;

+CONST int FTW_PHYS, FTW_MOUNT, FTW_DEPTH, FTW_CHDIR ;
+CONST int FTW_DP, FTW_SL ;

+FIELD struct FTW {
    int base ;
    int level ;
} ;

+FUNC int nftw ( const char *,
    int (*) ( const char *, const struct stat *, int, struct FTW * ),
    int, int ) ;
