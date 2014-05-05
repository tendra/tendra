# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "", "config" ;

+IF %% __SYSV_REMOTE_SERVICES %%

+USE "svid3", "netconfig.h.ts" ;
+USE "svid3", "tiuser.h.ts" ;

+FIELD struct nd_hostserv {
    char *h_host ;
    char *h_serv ;
} ;

+FIELD struct nd_addrlist {
    int n_cnt ;
    struct netbuf *n_addrs ;
} ;

+FIELD struct nd_hostservlist {
    int h_cnt ;
    struct nd_hostserv *h_hostservs ;
} ;

+CONST char *HOST_SELF, *HOST_ANY, *HOST_BROADCAST ;

+FUNC void netdir_free ( void *, int ) ;
+FUNC int netdir_getbyname ( const struct netconfig *,
    const struct nd_hostserv *, struct nd_addrlist ** ) ;
+FUNC int netdir_getbyaddr ( const struct netconfig *,
    struct nd_hostservlist **, const struct netbuf * ) ;
+FUNC char *taddr2uaddr ( const struct netconfig *, const struct netbuf * ) ;
/* I think these are wrong in the book */
+FUNC int netdir_options ( const struct netconfig *, int, int, void * ) ;
+FUNC struct netbuf *uaddr2taddr ( const struct netconfig *, const char * ) ;

+ENDIF
