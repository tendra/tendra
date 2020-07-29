# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE ( "c/c89" ), "errno.h.ts" ;

/* Only BSD specific error numbers given */
+CONST int EADDRINUSE, EADDRNOTAVAIL, EAFNOSUPPORT, EALREADY ;
+CONST int ECONNREFUSED, EINPROGRESS, EISCONN, EMSGSIZE, ENETUNREACH ;
+CONST int ENOBUFS, ENOTCONN, ENOTSOCK, EOPNOTSUPP, EPROTONOSUPPORT ;
+CONST int EPROTOTYPE, ETIMEDOUT, EWOULDBLOCK ;
