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
+IF %% __SYSV_AUDITING_EXTENSION %%
+USE "svid3", "sys/types.h" ;

+CONST int ABUFGET, ABUFSET ;
+CONST int AUDITON, AUDITOFF, ASTATUS ;
+CONST int AGETSYS, ASETSYS, AGETUSR, ASETME, AGETLVL, ACNTLVL, ASETLVL ;
+CONST int ASETUSR, AYAUDIT, ANAUDIT ;
+CONST int ADT_LMASK, ADT_RMASK, ADT_OMASK ;
+CONST int PPATH, PNODE, APATH, ANODE, PSIZE, PSPECIAL, ASPECIAL ;
+CONST int ASHUT, AALOG, APROG, ADISA ;
+CONST int ALOGGET, ALOGSET ;

+FIELD struct abuf {
    int vhigh ;
    int bsize ;
} ;

+CONST int ADT_VERLEN ;
+NAT ~ADT_VERLEN ;

+FIELD struct actl {
    int auditon ;
    char version [ ~ADT_VERLEN ] ;
    long gmtsecoff ;
} ;

+FIELD struct arec {
    int rtype ;
    int rstatus ;
    int rsize ;
    char *argp ;
} ;

+TYPE adtemask_t ;

+FIELD struct aevt {
    adtemask_t emask ;
    uid_t uid ;
    unsigned int flags ;
    unsigned int nlvls ;
    level_t *lvl_minp ;
    level_t *lvl_maxp ;
    level_t *lvl_tblp ;
} ;

+CONST int ADT_DATESZ, ADT_NODESZ ;
+NAT ~ADT_DATESZ, ~ADT_NODESZ ;

+FIELD struct alog {
    int flags ;
    int onfull ;
    int onerr ;
    int maxsize ;
    int seqnum ;
    char mmp [ ~ADT_DATESZ ] ;
    char ddp [ ~ADT_DATESZ ] ;
    char pnodep [ ~ADT_NODESZ ] ;
    char anodep [ ~ADT_NODESZ ] ;
    char *ppathp ;
    char *apathp ;
    char *progp ;
    char *defpathp ;
    char *defnodep ;
    char *defpgmp ;
    int defonfull ;
} ;

+FUNC int auditbuf ( int, struct abuf *, int ) ;
+FUNC int auditctl ( int, struct actl *, int ) ;
+FUNC int auditdmp ( struct arec *, int ) ;
+FUNC int auditevt ( int, struct aevt *, int ) ;
+FUNC int auditlog ( int, struct alog *, int ) ;

+ENDIF
