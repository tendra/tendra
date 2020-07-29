# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "bsd_extn", "sys/types.h.ts" ;
+USE "bsd_extn", "sys/time.h.ts" (!?) ;
+USE "bsd_extn", "sys/uio.h.ts" ;

+TYPE fd_set ;

+FUNC int select ( int, fd_set *, fd_set *, fd_set *, struct timeval * ) ;

+MACRO void FD_SET ( int, fd_set * ) ;
+MACRO void FD_CLR ( int, fd_set * ) ;
+MACRO int FD_ISSET ( int, fd_set * ) ;
+MACRO void FD_ZERO ( fd_set * ) ;
