# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "", "config" ;

+IF %% __SYSV_REMOTE_ADMINISTRATION %%

+CONST int APPEND, UPDATE, READ ;

+CONST int ST_QUEUED, ST_INPROGRESS, ST_SUCCEEDED, ST_FAILED ;
+CONST int ST_CANCELLED, ST_TIMEOUT, ST_REJECTED ;

+FIELD struct remop | remop_struct {
    char *machine ;
    int sid ;
    int adminid ;
    int primid ;
    int depend_flg ;
    int dependid ;
    int exit_status ;
    int filler ;
    struct remop *next ;
} ;

+CONST int DST_LEN, SVC_LEN, PRIM_LEN, NS_LEN ;
+NAT ~DST_LEN, ~SVC_LEN, ~PRIM_LEN, ~NS_LEN ;

+FIELD struct job_record {
    long rtime ;
    int sid ;
    int adminid ;
    int primid ;
    int stat ;
    char dst [ ~DST_LEN ] ;
    char svc [ ~SVC_LEN ] ;
    char prim [ ~PRIM_LEN ] ;
    char ns [ ~NS_LEN ] ;
} ;

+FIELD struct stringll {
    char *name ;
    char *value ;
    struct stringll *next ;
} ;

+FUNC int mgroup ( const char *, struct remop ** ) ;
+FUNC int remop ( const char *, const char *, const char *, struct remop *,
		  const char *, const char * ) ;
+FUNC char *roigetuser ( char * ) ;
+FUNC int roijobids ( int, int * ) ;
+FUNC int roistat ( int, const char *, struct job_record * ) ;
+FUNC int roitosparse ( const char *, struct stringll ** ) ;
+FUNC int roitosval ( struct stringll *, const char * ) ;

+ENDIF
