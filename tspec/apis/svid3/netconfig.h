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
