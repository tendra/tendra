#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
+USE "svid3", "", "config" ;

+IF %% __SYSV_REMOTE_SERVICES %%

+USE "svid3", "netconfig.h" ;
+USE "svid3", "tiuser.h" ;

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
