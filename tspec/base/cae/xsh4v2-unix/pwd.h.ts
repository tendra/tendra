# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+USE "cae/xsh4-base", "pwd.h.ts" ;

+FUNC void endpwent ( void ) ;
+FUNC struct passwd *getpwent ( void ) ;
+FUNC void setpwent ( void ) ;

/*
 * XPG4v2 specifies "getpmsg - get user database entry" in <pwd.h> for UNIX95.
 * Synopsis on page 260 of c435.pdf:
 *
 *  #include <pwd.h>
 *  int getpmsg(int, struct strbuf *, struct strbuf *, int *, int *);
 *
 * I believe this to be incorrect; I think that page should have listed getpmsg()
 * for <stropts.h>. Meanwhile, "get user database entry" is the description for
 * getpwent() in <pwd.h>, given on page 264.
 */

