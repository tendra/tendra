# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "bsd_extn", "sys/types.h.ts" ;

+CONST int PF_UNIX, PF_INET ;
+CONST int SOCK_STREAM, SOCK_DGRAM, SOCK_RAW, SOCK_SEQPACKET, SOCK_RDM ;

+FUNC int socket ( int, int, int ) ;
+FUNC int socketpair ( int, int, int, int [2] ) ;

+CONST int SO_DEBUG, SO_REUSEADDR, SO_KEEPALIVE, SO_DONTROUTE, SO_LINGER ;
+CONST int SO_BROADCAST, SO_SNDBUF, SO_RCVBUF ;
# SO_OOBINLINE, SO_TYPE, SO_ERROR

+FUNC int getsockname ( int, caddr_t, int * ) ;
+FUNC int getsockopt ( int, int, int, char *, int * ) ;
+FUNC int setsockopt ( int, int, int, const char *, int ) ;
+FUNC int getpeername ( int, caddr_t, int * ) ;

+CONST int MSG_OOB, MSG_DONTROUTE, MSG_PEEK ;

+FIELD struct msghdr {
    caddr_t msg_name ;
    int msg_namelen ;
    struct iovec *msg_iov ;
    int msg_iovlen ;
    caddr_t msg_accrights ;
    int msg_accrightslen ;
} ;

+FUNC int accept ( int, caddr_t, int * ) ;
+FUNC int bind ( int, caddr_t, int ) ;
+FUNC int connect ( int, caddr_t, int ) ;
+FUNC int listen ( int, int ) ;
+FUNC int shutdown ( int, int ) ;
+FUNC int recv ( int, char *, int, int ) ;
+FUNC int recvfrom ( int, char *, int, int, caddr_t, int * ) ;
+FUNC int recvmsg ( int, struct msghdr *, int ) ;
+FUNC int send ( int, const char *, int, int ) ;
+FUNC int sendto ( int, const char *, int, int, caddr_t, int ) ;
+FUNC int sendmsg ( int, struct msghdr *, int ) ;
