# $Id$

# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+USE "c/c89", "stddef.h.ts", "size_t" (!?);

+IMPLEMENT "cae/xns5-ar", "netinet/in.h", "port_addr" (!?);
+IMPLEMENT "sus/xsh2", "inttypes.h.ts"; # explicitly #include

+FIELD struct hostent {
	char *h_name;
	char **h_aliases;
	int h_addrtype;
	int h_length;
	char **h_addr_list;
};

+FIELD struct netent {
	char *n_name;
	char **n_aliases;
	int n_addrtype;
	uint32_t n_net;
};

+FIELD struct protoent {
	char *p_name;
	char **p_aliases;
	int p_proto;
};

+FIELD struct servent {
	char *s_name;
	char **s_aliases;
	int s_port;
	char *s_proto;
};

+CONST unsigned IPPORT_RESERVED;

+EXP (extern) int h_errno;
+CONST int HOST_NOT_FOUND;
+CONST int NO_DATA;
+CONST int NO_RECOVERY;
+CONST int TRY_AGAIN;

+FUNC void             endhostent(void);
+FUNC void             endnetent(void);
+FUNC void             endprotoent(void);
+FUNC void             endservent(void);
+FUNC struct hostent  *gethostbyaddr(const void *addr, size_t len, int type);
+FUNC struct hostent  *gethostbyname(const char *name);
+FUNC struct hostent  *gethostent(void);
+FUNC struct netent   *getnetbyaddr(uint32_t net, int type);
+FUNC struct netent   *getnetbyname(const char *name);
+FUNC struct netent   *getnetent(void);
+FUNC struct protoent *getprotobyname(const char *name);
+FUNC struct protoent *getprotobynumber(int proto);
+FUNC struct protoent *getprotoent(void);
+FUNC struct servent  *getservbyname(const char *name, const char *proto);
+FUNC struct servent  *getservbyport(int port, const char *proto);
+FUNC struct servent  *getservent(void);
+FUNC void             sethostent(int stayopen);
+FUNC void             setnetent(int stayopen);
+FUNC void             setprotoent(int stayopen);
+FUNC void             setservent(int stayopen);

