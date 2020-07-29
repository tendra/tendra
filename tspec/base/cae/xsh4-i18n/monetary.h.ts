# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "posix/posix1", "sys/types.h.ts", "ssize_t" ;
+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" ;

+FUNC ssize_t strfmon ( char *, size_t, const char *, ... ) ;

