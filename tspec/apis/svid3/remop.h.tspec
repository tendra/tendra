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
