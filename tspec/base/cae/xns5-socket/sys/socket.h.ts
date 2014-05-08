# $Id$

# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+USE "c/c89", "stddef.h.ts", "size_t"        (!?);
+USE "cae/xsh5", "sys/types.h.ts", "ssize_t" (!?);
+USE "cae/xsh5", "sys/uio.h.ts", "iovec"     (!?);

+TYPE (unsigned) socklen_t; # at least 32 bits

+SUBSET "sa_family_t" := {
	+TYPE (unsigned) sa_family_t;
};

+NAT ~sockaddr_sa_data_size;
+FIELD struct sockaddr {
	sa_family_t sa_family;
	char sa_data[~sockaddr_sa_data_size];
};

+FIELD struct msghdr {
	void *msg_name;
	socklen_t msg_namelen;
	struct iovec *msg_iov;
	int msg_iovlen;
	void *msg_control;
	socklen_t msg_controllen;
	int msg_flags;
};

+FIELD struct cmsghdr {
	socklen_t cmsg_len;
	int cmsg_level;
	int csmg_type;
};

+MACRO unsigned char *CMSG_DATA(struct cmsghdr *);
+MACRO struct cmsghdr *CMSG_NXTHDR(struct msghdr *, struct cmsghdr *);
+MACRO struct cmsghdr *CMSG_FIRSTHDR(struct msghdr *);

+FIELD struct linger {
	int l_onoff;
	int l_linger;
};

# XXX: these are all mandated to be macros
+TYPE (int) ~socket_sock;
+TYPE (int) ~socket_sol;
+TYPE (int) ~socket_so;
+TYPE (int) ~socket_msg;
+TYPE (int) ~socket_af;
+TYPE (int) ~socket_shut;
+CONST ~socket_sock SOCK_DGRAM, SOCK_STREAM, SOCK_SEQPACKET;
+CONST ~socket_sol SOL_SOCKET;
+CONST ~socket_so SO_ACCEPTCONN, SO_BROADCAST, SO_DEBUG, SO_DONTROUTE, SO_ERROR,
                  SO_KEEPALIVE, SO_LINGER, SO_OOBINLINE,
                  SO_RCVBUF, SO_RCVLOWAT, SO_RCVTIMEO,
                  SO_REUSEADDR, SO_SNDBUF, SO_SNDLOWAT, SO_SNDTIMEO, SO_TYPE;
+CONST ~socket_msg MSG_CTRUNC, MSG_DONTROUTE, MSG_EOR, MSG_OOB, MSG_PEEK,
                   MSG_TRUNC, MSG_WAITALL;
+CONST ~socket_af AF_UNIX, AF_UNSPEC, AF_INET;
+CONST ~socket_shut SHUT_RD, SHUT_WR, SHUT_RDWR;

+FUNC int accept(int socket, struct sockaddr *address, socklen_t *address_len);
+FUNC int bind(int socket, const struct sockaddr *address, socklen_t address_len);
+FUNC int connect(int socket, const struct sockaddr *address, socklen_t address_len);
+FUNC int getpeername(int socket, struct sockaddr *address, socklen_t *address_len);
+FUNC int getsockname(int socket, struct sockaddr *address, socklen_t *address_len);
+FUNC int getsockopt(int socket, int level, int option_name, void *option_value, socklen_t *option_len);
+FUNC int listen(int socket, int backlog);

+FUNC ssize_t recv(int socket, void *buffer, size_t length, int flags);
+FUNC ssize_t recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len);
+FUNC ssize_t recvmsg(int socket, struct msghdr *message, int flags);
+FUNC ssize_t send(int socket, const void *message, size_t length, int flags);
+FUNC ssize_t sendmsg(int socket, const struct msghdr *message, int flags);
+FUNC ssize_t sendto(int socket, const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);

+FUNC int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
+FUNC int shutdown(int socket, int how);
+FUNC int socket(int domain, int type, int protocol);
+FUNC int socketpair(int domain, int type, int protocol, int socket_vector[2]);

