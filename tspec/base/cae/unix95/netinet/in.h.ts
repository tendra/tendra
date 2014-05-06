# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# CAE, Networking Services, Issue 4

+USE "cae/unix95", "sys/socket.h.ts" ;
+IMPLEMENT "cae/unix95", "sys/socket.h.ts", "sa_family_t" ;

+SUBSET "in_t" := {
    +TYPE ( unsigned ) in_port_t ;	# 16 bits
    +TYPE ( unsigned ) in_addr_t ;	# 32 bits
} ;

+FIELD struct in_addr {
    in_addr_t s_addr ;
} ;

+FIELD struct sockaddr_in {
    sa_family_t sin_family ;
    in_port_t sin_port ;
    struct in_addr sin_addr ;
    unsigned char sin_zero [ 8 ] ;
} ;

# level of getsockopt and setsockopt
+CONST int IPPROTO_IP, IPPROTO_ICMP, IPPROTO_TCP, IPPROTO_UDP ;

# destination addresses
+EXP const struct sockaddr * INADDR_ANY ;
+EXP const struct sockaddr * INADDR_BROADCAST ;
