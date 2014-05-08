# $Id$

# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "cae/xns5-ar", "netinet/in.h.ts", "port_addr" (!?);
+IMPLEMENT "cae/xns5-ar", "netinet/in.h.ts", "in_addr"   (!?);

+SUBSET "endian" := {
	+USE "cae/xsh5", "inttypes.h.ts";

	+FUNC uint32_t htonl(uint32_t hostlong);
	+FUNC uint16_t htons(uint16_t hostshort);
	+FUNC uint32_t ntohl(uint32_t netlong);
	+FUNC uint16_t ntohs(uint16_t netshort);
};

+FUNC in_addr_t      inet_addr(const char *cp);
+FUNC in_addr_t      inet_lnaof(struct in_addr in);
+FUNC struct in_addr inet_makeaddr(in_addr_t net, in_addr_t lna);
+FUNC in_addr_t      inet_netof(struct in_addr in);
+FUNC in_addr_t      inet_network(const char *cp);
+FUNC char          *inet_ntoa(struct in_addr in);

