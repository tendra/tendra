# $Id$

# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "cae/xns5-socket", "sys/socket.h.ts", "sa_family_t" (!?);

+NAT ~local_sockaddr_un_path_size;
+FIELD struct sockaddr_un {
	sa_family_t sun_family;
	char sun_path[~local_sockaddr_un_path_size];
};

