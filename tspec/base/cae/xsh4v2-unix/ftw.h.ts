# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "cae/xsh4v2-unix", "sys/stat.h.ts", "st_proto" ;

+FIELD struct FTW {
	int base ;
	int level ;
} ;

+CONST int FTW_SL, FTW_SLN ;
+CONST int FTW_PHYS, FTW_MOUNT, FTW_DEPTH, FTW_CHDIR ;

+FUNC int nftw ( const char *,
    int (*) ( const char *, const struct stat *, int, struct FTW * ),
    int, int ) ;

