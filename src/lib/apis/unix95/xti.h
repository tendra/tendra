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
# CAE, Networking Services, Issue 4

# Events
+CONST int T_LISTEN, T_CONNECT, T_DATA, T_EXDATA, T_DISCONNECT, T_ORDREL ;
+CONST int T_UDERR ;
+CONST int T_GODATA, T_GOEXDATA ;

# States
+CONST int T_UNINIT, T_UNBND, T_IDLE, T_OUTCON, T_INCON, T_DATAXFER ;
+CONST int T_INREL, T_OUTREL ;

# Service types
+CONST int T_COTS, T_COTS_ORD, T_CLTS ;

# Errors
+CONST int TBADADDR, TBADOPT, TACCES, TBADF, TNOADDR, TOUTSTATE, TBADSEQ ;
+CONST int TSYSERR, TLOOK, TBADDATA, TBUFOVFLW, TFLOW, TNODATA, TNODIS ;
+CONST int TNOUDERR, TBADFLAG, TNOREL, TNOTSUPPORT, TSTATECHNG, TNOSTRUCTYPE ;
+CONST int TBADNAME, TBADQLEN, TADDRBUSY ;
+CONST int TINDOUT, TPROVMISMATCH, TRESQLEN, TRESADDR, TQFULL, TPROTO ;

# Structure types for t_alloc
+CONST int T_BIND, T_CALL, T_OPTMGMT, T_DIS, T_UNITDATA, T_UDERROR, T_INFO ;

# Fields for t_alloc
+CONST int T_ADDR, T_OPT, T_UDATA, T_ALL ;

# Flags for t_optmgmt
+CONST int T_NEGOTIATE, T_CHECK, T_DEFAULT, T_CURRENT ;
+CONST int T_ALLOPT ;

# XTI level options for t_optmgmt
+CONST int XTI_GENERIC ;
+CONST int XTI_DEBUG, XTI_LINGER, XTI_RCVBUF, XTI_RCVLOWAT ;
+CONST int XTI_SNDBUF, XTI_SNDLOWAT ;

# l_onoff of struct t_linger
+CONST int T_YES, T_NO ;

# l_linger of struct t_linger
+CONST int T_UNSPEC, T_INFINITE ;

# Flags for t_send
+CONST int T_EXPEDITED, T_MORE ;

# Flags of struct t_info
+CONST long T_SENDZERO ;

# Status of struct t_opthdr
+CONST unsigned long T_SUCCESS, T_FAILURE, T_PARTSUCCESS ;
+CONST unsigned long T_READONLY, T_NOTSUPPORT ;

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
    long flags ;
} ;

+FIELD struct t_optmgmt | t_optmgmt_struct {
    struct netbuf opt ;
    long flags ;
} ;

+FIELD struct t_opthdr {
    unsigned long len ;
    unsigned long level ;
    unsigned long name ;
    unsigned long status ;
} ;

+MACRO struct t_opthdr * OPT_NEXTHDR ( char *, long, struct t_opthdr * ) ;

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

+FIELD struct t_linger := {
    long l_onoff ;
    long l_linger ;
} ;

# Error handling
+EXP (extern) int t_errno ;

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
+FUNC char * t_strerror ( int ) ;
+FUNC int t_getinfo ( int, struct t_info * ) ;
+FUNC int t_getprotaddr( int, struct t_bind *, struct t_bind * ) ;
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

+FIELD struct transdel {
    struct reqvalue maxdel ;
    struct reqvalue avgdel ;
} ;

# Protocol level
+CONST int ISO_TP ;

# Connection-mode quality of service options
+CONST int TCO_THROUGHPUT, TCO_TRANSDEL, TCO_RESERRORRATE ;
+CONST int TCO_TRANSFFAILPROB, TCO_ESTFAILPROB, TCO_RELFAILPROB ;
+CONST int TCO_ESTDELAY, TCO_RELDELAY, TCO_CONNRESIL ;
+CONST int TCO_PROTECTION, TCO_PRIORITY, TCO_EXPD ;

# Connection-mode management options
+CONST int TCO_LTPDU, TCO_ACKTIME, TCO_REASTIME, TCO_PREFCLASS ;
+CONST int TCO_ALTCLASS1, TCO_ALTCLASS2, TCO_ALTCLASS3, TCO_ALTCLASS4 ;
+CONST int TCO_EXTFORM, TCO_FLOWCTRL, TCO_CHECKSUM, TCO_NETEXP, TCO_NETRECPTCF ;

# Various extra codes
+CONST int T_CLASS0, T_CLASS1, T_CLASS2, T_CLASS3, T_CLASS4 ;
+CONST int T_PRIDFLT, T_PRILOW, T_PRIMID, T_PRIHIGH, T_PRITOP ;
+CONST int T_NOPROTECT, T_PASSIVEPROTECT, T_ACTIVEPROTECT ;
+CONST int T_ABSREQ ;

# Connectionless-mode quality of service options
+CONST int TCL_TRANSDEL, TCL_RESERRORRATE, TCL_PROTECTION, TCL_PRIORITY ;

# Connectionless-mode management options
+CONST int TCL_CHECKSUM ;

# Appendix B

# Protocol levels
+CONST int INET_TCP, INET_UDP, INET_IP ;

# TCP options
+CONST int TCP_KEEPALIVE, TCP_MAXSEG, TCP_NODELAY ;

+FIELD struct t_kpalive := {
    long kp_onoff ;
    long kp_timeout ;
} ;

# kp_onoff of struct t_kpalive
+CONST int T_GARBAGE ;

# UDP options
+CONST int UDP_CHECKSUM ;

# IP options
+CONST int IP_BROADCAST, IP_DONTROUTE, IP_OPTIONS ;
+CONST int IP_REUSEADDR, IP_TOS, IP_TTL ;

# IP_TOS precedence
+CONST int T_ROUTINE, T_PRIORITY, T_IMMEDIATE, T_FLASH, T_OVERRIDEFLASH ;
+CONST int T_CRITIC_ECP, T_INETCONTROL, T_NETCONTROL ;

# IP_TOS service
+CONST int T_NOTOS, T_LDELAY, T_HITHRPT, T_HIREL ;

# Appendix D - NetBIOS

+DEFINE NB_UNIQUE 0 ;
+DEFINE NB_GROUP 1 ;
+DEFINE NB_NAMELEN 16 ;
+DEFINE NB_BCAST_NAME %% "*               " %% ;

+DEFINE NB_ABORT %% 0x18 %% ;
+DEFINE NB_CLOSED %% 0x0A %% ;
+DEFINE NB_NOANSWER %% 0x14 %% ;
+DEFINE NB_OPREJ %% 0x12 %% ;

# Appendix I - SNA

# SNA transport provider option not specified
