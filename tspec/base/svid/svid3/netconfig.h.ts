# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;

+IF %% __SYSV_REMOTE_SERVICES %%

/* The nc_proto and nc_protofmly fields are wrong in the book */
+FIELD struct netconfig {
    char *nc_netid ;
    unsigned long nc_semantics ;
    unsigned long nc_flag ;
    char *nc_proto ;
    char *nc_protofmly ;
    char *nc_device ;
    unsigned long nc_nlookups ;
    char **nc_lookups ;
} ;

+CONST int NC_TPI_COTS, NC_TPI_COTS_ORD, NC_TPI_CLTS ;
+CONST int NC_VISIBLE, NC_NOFLAG ;

+FUNC struct netconfig *getnetconfig ( void * ) ;
+FUNC void *setnetconfig ( void ) ;
+FUNC int endnetconfig ( void * ) ;
+FUNC struct netconfig *getnetconfigent ( char * ) ;
/* Error in book */
+FUNC void freenetconfigent ( struct netconfig * ) ;
+FUNC struct netconfig *getnetpath ( void * ) ;
+FUNC void *setnetpath ( void  ) ;
+FUNC int endnetpath ( void * ) ;
+FUNC void nc_perror ( char * ) ;

+ENDIF
