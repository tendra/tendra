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

+USE "unix95", "sys/types.h" ;
+USE "unix95", "sys/uio.h" ;

+CONST int SCM_RIGHTS ;

+CONST int SOCK_DGRAM, SOCK_STREAM, SOCK_SEQPACKET ;

+CONST int SOL_SOCKET ;

+CONST int SO_DEBUG, SO_ACCEPTCONN, SO_BROADCAST, SO_REUSEADDR ;
+CONST int SO_KEEPALIVE, SO_LINGER, SO_OOBINLINE ;
+CONST int SO_SNDBUF, SO_RCVBUF, SO_ERROR, SO_TYPE ;

+CONST int MSG_CTRUNC, MSG_OOB, MSG_PEEK, MSG_TRUNC, MSG_WAITALL;

+CONST int AF_UNIX, AF_INET ;

+CONST int SHUT_RD, SHUT_WR, SHUT_RDWR ;

+SUBSET "sa_family_t" := { +TYPE (unsigned) sa_family_t ; } ;

+NAT ~sa_data_size ;

+FIELD struct sockaddr {
    sa_family_t sa_family ;
    char sa_data [ ~sa_data_size ] ;
} ;

+FIELD struct msghdr {
    void *msg_name ;
    size_t msg_namelen ;
    struct iovec *msg_iov ;
    int msg_iovlen ;
    void *msg_control ;
    size_t msg_controllen ;
    int msg_flags ;
} ;

+FIELD struct cmsghdr {
    size_t cmsg_len ;
    int cmsg_level ;
    int cmsg_type ;
} ;

+FIELD struct linger {
    int l_onoff ;
    int l_linger ;
} ;

+MACRO unsigned char * CMSG_DATA ( struct cmsghdr * ) ;
+MACRO struct cmsghdr * CMSG_NXTHDR ( struct msghdr *, struct cmsghdr * ) ;
+MACRO struct cmsghdr * CMSG_FIRSTHDR ( struct msghdr * ) ;

+FUNC int accept ( int, struct sockaddr *, size_t * ) ;
+FUNC int bind ( int, const struct sockaddr *, size_t ) ;
+FUNC int connect ( int, const struct sockaddr *, size_t ) ;
+FUNC int getpeername ( int, const struct sockaddr *, size_t * ) ;
+FUNC int getsockname ( int, const struct sockaddr *, size_t * ) ;
+FUNC int getsockopt ( int, int, int, void *, size_t * ) ;
+FUNC int listen ( int, int ) ;
+FUNC ssize_t recv ( int, void *, size_t, int ) ;
+FUNC ssize_t recvfrom ( int, void *, size_t,
    int, struct sockaddr *, size_t * ) ;
+FUNC ssize_t recvmsg ( int, struct msghdr *, int ) ;
+FUNC ssize_t send ( int, const void *, size_t, int ) ;
+FUNC ssize_t sendmsg ( int, const struct msghdr *, int ) ;
+FUNC ssize_t sendto ( int, const void *, size_t, int,
    const struct sockaddr *, size_t ) ;
+FUNC int setsockopt ( int, int, int, const void *, size_t ) ;
+FUNC int shutdown ( int, int ) ;
+FUNC int socket ( int, int, int ) ;
+FUNC int socketpair ( int, int, int, int [2] ) ;
