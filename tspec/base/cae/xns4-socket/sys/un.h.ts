# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# CAE, Networking Services, Issue 4

+IMPLEMENT "cae/xns4-socket", "sys/socket.h.ts", "sa_family_t" ;

+NAT ~sun_path_size ;

+FIELD struct sockaddr_un {
    sa_family_t sun_family ;
    char sun_path [ ~sun_path_size ] ;
} ;
