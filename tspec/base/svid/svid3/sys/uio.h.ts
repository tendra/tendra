# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "sys/types.h.ts" (?!) ;

+FIELD struct iovec {
    char *iov_base ;
    int iov_len ;
} ;

+FUNC int readv ( int, struct iovec *, int ) ;
+FUNC int writev ( int, const struct iovec *, int ) ;
