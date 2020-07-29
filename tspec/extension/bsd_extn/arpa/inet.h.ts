# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "bsd_extn", "sys/types.h.ts" ;
+USE "bsd_extn", "netinet/in.h.ts" ;

+FUNC unsigned long inet_addr ( const char * ) ;
+FUNC unsigned long inet_network ( const char * ) ;
+FUNC struct in_addr inet_makeaddr ( int, int ) ;
+FUNC unsigned long inet_lnaof ( struct in_addr ) ;
+FUNC unsigned long inet_netof ( struct in_addr ) ;
+FUNC char *inet_ntoa ( struct in_addr ) ;
