# $Id$

# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+USE "cae/xsh5", "inttypes.h.ts";
+IMPLEMENT "cae/xns5-ar", "netinet/in.h.ts", "in_t" ;

+TYPEDEF uint16_t ~to_port_t ;
+TYPEDEF uint32_t ~to_addr_t ;

+IMPLEMENT "cae/xns4-ar", "arpa/inet.h.ts", "inet_generic";

