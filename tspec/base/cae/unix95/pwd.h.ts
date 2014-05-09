# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "cae/xsh4-base", "pwd.h.ts" ;

+IMPLEMENT "posix/posix", "sys/types.h.ts", "guid" ;

+FUNC void endpwent ( void ) ;
+FUNC struct passwd *getpwent ( void ) ;
+FUNC void setpwent ( void ) ;
