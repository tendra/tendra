# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "sys/types.h.ts" (?!) ;

+CONST int FSTYPSZ ;
+NAT ~FSTYPSZ ;

+FIELD struct statvfs | statvfs_struct {
    unsigned long f_bsize ;
    unsigned long f_frsize ;
    unsigned long f_blocks ;
    unsigned long f_bfree ;
    unsigned long f_bavail ;
    unsigned long f_files ;
    unsigned long f_ffree ;
    unsigned long f_favail ;
    unsigned long f_fsid ;
    char f_basetype [ ~FSTYPSZ ] ;
    unsigned long f_flag ;
    unsigned long f_namemax ;
    char f_fstr [32] ;
} ;

+CONST int ST_RDONLY, ST_NOSUID ;
+FUNC int statvfs ( const char *, struct statvfs * ) ;
+FUNC int fstatvfs ( int, struct statvfs * ) ;
