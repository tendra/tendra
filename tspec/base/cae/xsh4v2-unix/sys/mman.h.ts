# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" ;
+IMPLEMENT "posix/posix", "sys/types.h.ts", "off_t" ;

+CONST int PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE ;
+CONST int MAP_SHARED, MAP_PRIVATE, MAP_FIXED ;
+CONST int MS_ASYNC, MS_SYNC, MS_INVALIDATE ;

+FUNC void *mmap ( void *, size_t, int, int, int, off_t ) ;
+FUNC int mprotect ( void *, size_t, int ) ;
+FUNC int msync ( void *, size_t, int ) ;
+FUNC int munmap ( void *, size_t ) ;
