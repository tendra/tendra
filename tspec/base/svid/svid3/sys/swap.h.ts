# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IF %% __SYSV_REAL_TIME %%
+USE "svid/svid3", "sys/types.h.ts" ;

+CONST int SC_ADD, SC_LIST, SC_REMOVE, SC_GETNSWP ;

+FIELD struct swapres {
    char *sr_name ;
    off_t sr_start ;
    off_t sr_length ;
} ;

+FIELD struct swapent {
    char *ste_path ;
    off_t ste_start ;
    off_t ste_length ;
    long ste_pages ;
    long ste_free ;
    long ste_flags ;
} ;

/* Is this right? */
+FIELD struct swaptable {
    int swt_n ;
    struct swapent swt_ent [1] ;
} ;

+FUNC int swapctl ( int, void * ) ;

+ENDIF
