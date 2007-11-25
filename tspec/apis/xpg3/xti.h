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
+IF 0 # FOR THE MOMENT

# NETWORKING SERVICES

# Events
+CONST int T_LISTEN, T_CONNECT, T_DATA, T_EXDATA, T_DISCONNECT, T_ORDREL ;
+CONST int T_UDERR, T_GODATA, T_GOEXDATA ;

# States
+CONST int T_UNINIT, T_UNBND, T_IDLE, T_OUTCON, T_INCON, T_DATAXFER ;
+CONST int T_INREL, T_OUTREL ;

# Service types
+CONST int T_COTS, T_COTS_ORD, T_CLTS ;

# Errors
+CONST int TBADADDR, TBADOPT, TACCES, TBADF, TNOADDR, TOUTSTATE, TBADSEQ ;
+CONST int TSYSERR, TLOOK, TBADDATA, TBUFOVFLW, TFLOW, TNODATA, TNODIS ;
+CONST int TNOUDERR, TBADFLAG, TNOREL, TNOTSUPPORT, TSTATECHNG, TNOSTRUCTYPE;
+CONST int TBADNAME, TBADQLEN, TADDRBUSY ;

# Structure types for t_alloc
+CONST int T_BIND_STR, T_CALL_STR, T_OPTMGMT_STR, T_DIS_STR, T_UNITDATA_STR ;
+CONST int T_UDERROR_STR, T_INFO_STR ;

# Fields for t_alloc
+CONST int T_ADDR, T_OPT, T_UDATA, T_ALL ;

# Flags for t_optmgmt
+CONST int T_NEGOTIATE, T_CHECK, T_DEFAULT ;

# Flags for t_send
+CONST int T_EXPEDITED, T_MORE ;

# Structures

+FIELD struct netbuf {
    unsigned int maxlen ;
    unsigned int len ;
    char *buf ;
} ;

+FIELD struct t_call {
    struct netbuf addr ;
    struct netbuf opt ;
    struct netbuf udata ;
    int sequence ;
} ;

+FIELD struct t_bind | t_bind_struct {
    struct netbuf addr ;
    unsigned int qlen ;
} ;

+FIELD struct t_info {
    long addr ;
    long options ;
    long tsdu ;
    long etsdu ;
    long connect ;
    long discon ;
    long servtype ;
} ;

+FIELD struct t_optmgmt | t_optmgmt_struct {
    struct netbuf opt ;
    long flags ;
} ;

+FIELD struct t_discon {
    struct netbuf udata ;
    int reason ;
    int sequence ;
} ;

+FIELD struct t_unitdata {
    struct netbuf addr ;
    struct netbuf opt ;
    struct netbuf udata ;
} ;

+FIELD struct t_uderr {
    struct netbuf addr ;
    struct netbuf opt ;
    long error ;
} ;

# Error handling
%%
extern int t_errno ;
extern char *t_errlist [] ;
extern int t_nerr ;
%%

# Functions

+FUNC int t_bind ( int, struct t_bind *, struct t_bind * ) ;
+FUNC int t_close ( int ) ;
+FUNC int t_look ( int ) ;
+FUNC int t_open ( char *, int, struct t_info * ) ;
+FUNC int t_sync ( int ) ;
+FUNC int t_unbind ( int ) ;

+FUNC int t_accept ( int, int, struct t_call * ) ;
+FUNC int t_connect ( int, struct t_call *, struct t_call * ) ;
+FUNC int t_listen ( int, struct t_call * ) ;
+FUNC int t_rcv ( int, char *, unsigned, int * ) ;
+FUNC int t_rcvconnect ( int, struct t_call * ) ;
+FUNC int t_rcvdis ( int, struct t_discon * ) ;
+FUNC int t_snd ( int, char *, unsigned, int ) ;
+FUNC int t_snddis ( int, struct t_call * ) ;

+FUNC int t_rcvrel ( int ) ;
+FUNC int t_sndrel ( int ) ;

+FUNC int t_rcvudata ( int, struct t_unitdata *, int * ) ;
+FUNC int t_rcvuderr ( int, struct t_uderr * ) ;
+FUNC int t_sndudata ( int, struct t_unitdata * ) ;

+FUNC int t_error ( char * ) ;
+FUNC int t_getinfo ( int, struct t_info * ) ;
+FUNC int t_getstate ( int ) ;
+FUNC int t_optmgmt ( int, struct t_optmgmt *, struct t_optmgmt * ) ;
+FUNC char *t_alloc ( int, int, int ) ;
+FUNC int t_free ( char *, int ) ;

# Appendix A

+FIELD struct rate {
    long targetvalue ;
    long minacceptvalue ;
} ;

+FIELD struct reqvalue {
    struct rate called ;
    struct rate calling ;
} ;

+FIELD struct thrpt {
    struct reqvalue maxthrpt ;
    struct reqvalue avgthrpt ;
} ;

+FIELD struct management {
    short dflt ;
    int ltpdu ;
    short reastime ;
    char class ;
    char altclass ;
    char extform ;
    char flowctrl ;
    char checksum ;
    char netexp ;
    char netrecptcf ;
} ;

+FIELD struct isoco_options {
    struct thrpt throughput ;
    struct reqvalue transdel ;
    struct rate reserrorrate ;
    struct rate transffailprob ;
    struct rate estfailprob ;
    struct rate relfailprob ;
    struct rate estdelay ;
    struct rate reldelay ;
    struct netbuf connresil ;
    unsigned short protection ;
    short priority ;
    struct management mngmt ;
    char expd ;
} ;

+CONST int T_UNUSED ;
+CONST int T_YES, T_NO ;
+CONST int T_CLASS0, T_CLASS1, T_CLASS2, T_CLASS3, T_CLASS4 ;
+CONST int T_PRIDFLT, T_PRILOW, T_PRIMID, T_PRIHIGH, T_PRITOP ;
+CONST int T_NOPROTECT, T_PASSIVEPROTECT, T_ACTIVEPROTECT ;
+CONST int T_ABSREQ ;
+CONST int T_LTPDUDFLT ;

+FIELD struct isocl_options {
    struct rate transdel ;
    struct rate reserrorrate ;
    unsigned short protection ;
    short priority ;
} ;


# Appendix B

+FIELD struct secoptions {
    short security ;
    short compartment ;
    short handling ;
    long tcc ;
} ;

+FIELD struct tcp_options {
    short precedence ;
    long timeout ;
    long max_seg_size ;
    struct secoptions secopt ;
} ;

+CONST int T_ROUTINE, T_PRIORITY, T_IMMEDIATE, T_FLASH, T_OVERRIDEFLASH ;
+CONST int T_CRITIC_ECP, T_INETCONTROL, T_NETCONTROL ;

+ENDIF
