# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Corrigenda U013 1170/02: define uid_t and gid_t
+IMPLEMENT "posix", "sys/types.h.ts", "guid" ;

+CONST int I_PUSH, I_POP, I_LOOK, I_FLUSH, I_FLUSHBAND, I_SETSIG ;
+CONST int I_GETSIG, I_FIND, I_PEEK, I_SRDOPT, I_GRDOPT, I_NREAD ;
+CONST int I_FDINSERT, I_STR, I_SWROPT, I_GWROPT, I_SENDFD, I_RECVFD ;
+CONST int I_LIST, I_ATMARK, I_CKBAND, I_GETBAND, I_CANPUT, I_SETCLTIME ;
+CONST int I_GETCLTIME, I_LINK, I_UNLINK, I_PLINK, I_PUNLINK ;

# from I_FLUSH
+CONST int FLUSHR, FLUSHW, FLUSHRW ;

# from I_FLUSHBAND
+FIELD struct bandinfo {
    unsigned char bi_pri ;
    int bi_flag ;
} ;

# from I_SETSIG
+CONST int S_RDNORM, S_RDBAND, S_INPUT, S_HIPRI, S_OUTPUT, S_WRNORM ;
+CONST int S_WRBAND, S_MSG, S_ERROR, S_HANGUP, S_BANDURG ;

# from I_PEEK
+FIELD struct strbuf {
    int maxlen ;
    int len ;
    char *buf ;
} ;

+FIELD struct strpeek {
    struct strbuf ctlbuf ;
    struct strbuf databuf ;
    long flags ;
} ;

# from I_PEEK
+CONST int RS_HIPRI ;

# from I_SRDOPT
+CONST int RNORM, RMSGD, RMSGN, RPROTNORM, RPROTDAT, RPROTDIS ;

# from I_FDINSERT
+FIELD struct strfdinsert {
    struct strbuf ctlbuf ;
    struct strbuf databuf ;
    long flags ;
    int fildes ;
    int offset ;
} ;

# from I_STR
+FIELD struct strioctl {
    int ic_cmd ;
    int ic_timout ;
    int ic_len ;
    char *ic_dp ;
} ;

# from I_SWROPT
+CONST int SNDZERO ;

# from I_RECVFD
+FIELD struct strrecvfd {
    int fd ;
    uid_t uid ;
    gid_t gid ;
} ;

# from I_LOOK
+CONST int FMNAMESZ ;
+NAT ~FMNAMESZ_PLUS_ONE ;
+FIELD struct str_mlist {
    char l_name [ ~FMNAMESZ_PLUS_ONE ] ;
} ;

+FIELD struct str_list {
    int sl_nmods ;
    struct str_mlist *sl_modlist ;
} ;

# from I_ATMARK
+CONST int ANYMARK, LASTMARK ;

# from I_UNLINK
+CONST int MUXID_ALL ;

+CONST int MSG_HIPRI, MSG_BAND, MSG_ANY ;
+CONST int MORECTL, MOREDATA ;

+FUNC int isastream ( int ) ;
+FUNC int getmsg ( int, struct strbuf *, struct strbuf *, int * ) ;
+FUNC int getpmsg ( int, struct strbuf *, struct strbuf *, int *, int * ) ;
+FUNC int ioctl ( int, int, ... ) ;
+FUNC int putmsg ( int, const struct strbuf *, const struct strbuf *, int ) ;
+FUNC int putpmsg ( int, const struct strbuf *, const struct strbuf *,
		    int, int ) ;
+FUNC int fattach ( int, const char * ) ;
+FUNC int fdetach ( const char * ) ;
