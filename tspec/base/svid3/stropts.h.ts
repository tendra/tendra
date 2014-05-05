# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "sys/types.h.ts" ;

+FIELD struct strbuf {
    int maxlen ;
    int len ;
    char *buf ;
} ;

+FUNC int getmsg ( int, struct strbuf *, struct strbuf *, int * ) ;
+FUNC int getpmsg ( int, struct strbuf *, struct strbuf *, int *, int * ) ;
+FUNC int putmsg ( int, const struct strbuf *, const struct strbuf *, int ) ;
+FUNC int putpmsg ( int, const struct strbuf *, const struct strbuf *,
		    int, int ) ;

+CONST int RS_HIPRI, MSG_HIPRI, MSG_BAND, MSG_ANY ;
+CONST int MORECTL, MOREDATA ;

+FIELD struct bandinfo {
    unsigned char bi_pri ;
    int bi_flag ;
} ;

+FIELD struct strpeek {
    struct strbuf ctlbuf ;
    struct strbuf databuf ;
    long flags ;
} ;

+FIELD struct strfdinsert {
    struct strbuf ctlbuf ;
    struct strbuf databuf ;
    long flags ;
    int fildes ;
    int offset ;
} ;

+FIELD struct strioctl {
    int ic_cmd ;
    int ic_timout ;
    int ic_len ;
    char *ic_dp ;
} ;

+FIELD struct strrecvfd {
    int fd ;
    uid_t uid ;
    gid_t gid ;
    char fill [8] ;
} ;

+CONST int FMNAMESZ ;
+NAT ~FMNAMESZ_PLUS_ONE ;
+FIELD struct str_mlist {
    char l_name [ ~FMNAMESZ_PLUS_ONE ] ;
} ;

+FIELD struct str_list {
    int sl_nmods ;
    struct str_mlist *sl_modlist ;
} ;

+CONST int I_PUSH, I_POP, I_LOOK, I_FLUSH, I_FLUSHBAND, I_SETSIG, I_GETSIG ;
+CONST int I_FIND, I_PEEK, I_SRDOPT, I_GRDOPT, I_NREAD, I_FDINSERT, I_STR ;
+CONST int I_SWROPT, I_GWROPT, I_SENDFD, I_RECVFD, I_LIST, I_ATMARK, I_CKBAND ;
+CONST int I_GETBAND, I_CANPUT, I_SETCLTIME, I_GETCLTIME, I_LINK, I_UNLINK ;
+CONST int I_PLINK, I_PUNLINK ;
+CONST int FLUSHR, FLUSHW, FLUSHRW ;
+CONST int S_RDNORM, S_RDBAND, S_INPUT, S_HIPRI, S_OUTPUT, S_WRNORM ;
+CONST int S_WRBAND, S_MSG, S_ERROR, S_HANGUP, S_BANDURG ;
+CONST int RNORM, RMSGD, RMSGN, RPROTNORM, RPROTDAT, RPROTDIS ;
+CONST int SNDZERO ;
+CONST int ANYMARK, LASTMARK ;
+CONST int MUXID_ALL ;

+FUNC int isastream ( int ) ;

# SVID3 not clear on ioctl(), streams(BA_DEV) requires #include <stropts.h>
+FUNC int ioctl ( int, int, ... ) ;
