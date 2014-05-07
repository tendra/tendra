# $Id$

# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "cae/xns5-socket", "sys/socket.h.ts", "sa_family_t" (!?);
+IMPLEMENT "cae/xns5-ar", "arpa/inet.h.ts", "endian" (!?);

+SUBSET "port_addr" := {
	+TYPE (unsigned) in_port_t; # exactly 16-bit only
	+TYPE (unsigned) in_addr_t; # exactly 32-bit only
};

+SUBSET "in_addr" := {
	+FIELD struct in_addr {
		in_addr_t s_addr;
	};
};

+FIELD struct sockaddr_in {
	sa_family_t    sin_family;
	in_port_t      sin_port;
	struct in_addr sin_addr;
	unsigned char  sin_zero[8];
};

+TYPE struct sockaddr;

+CONST int IPPROTO_IP, IPPROTO_ICMP, IPPROTO_TCP, IPPROTO_UDP;
+CONST int INADDR_ANY, INADDR_BROADCAST;

