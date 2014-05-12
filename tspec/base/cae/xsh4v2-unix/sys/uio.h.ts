# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "cae/xsh4v2-unix", "sys/types.h.ts" ;

+FIELD struct iovec {
    void *iov_base ;
    size_t iov_len ;
} ;

+FUNC ssize_t readv ( int, const struct iovec *, int ) ;
+FUNC ssize_t writev ( int, const struct iovec *, int ) ;
