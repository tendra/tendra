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
+USE "bsd_extn", "sys/types.h" ;

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
