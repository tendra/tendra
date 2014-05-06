# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IF 0

+USE "svid/svid3", "sys/types.h.ts" ;

/* This is obsolete, use statvfs */
+FIELD struct ustat | ustat_struct {
    daddr_t f_tfree ;
    ino_t f_tinode ;
    char f_fname [6] ;
    char f_fpack [6] ;
} ;

+FUNC int ustat ( int, struct ustat * ) ;

+ENDIF
