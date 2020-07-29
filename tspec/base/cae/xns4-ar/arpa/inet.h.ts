# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# CAE, Networking Services, Issue 4

+IMPLEMENT "cae/xns4-ar", "netinet/in.h.ts", "in_t" ;

+TYPEDEF in_addr_t ~to_addr_t;
+TYPEDEF in_port_t ~to_port_t;

+SUBSET "inet_generic" := {
	+USE "cae/xns4-ar", "netinet/in.h.ts", "in_generic" ;

	# function, macro, or both; macro is minimal interface so maximally portable
	# XNS5 has these as uint32_t et al.
	+MACRO ~to_addr_t htonl ( ~to_addr_t ) ;
	+MACRO ~to_port_t htons ( ~to_port_t ) ;
	+MACRO ~to_addr_t ntohl ( ~to_addr_t ) ;
	+MACRO ~to_port_t ntohs ( ~to_port_t ) ;

	+FUNC in_addr_t inet_addr ( const char * ) ;
	+FUNC in_addr_t inet_lnaof ( struct in_addr ) ;
	+FUNC struct in_addr inet_makeaddr ( in_addr_t, in_addr_t ) ;
	+FUNC in_addr_t inet_netof ( struct in_addr ) ;
	+FUNC in_addr_t inet_network ( const char * ) ;
	+FUNC char *inet_ntoa ( struct in_addr ) ;
} ;

