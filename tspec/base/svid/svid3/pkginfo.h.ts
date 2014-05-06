# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;

+IF 0
+IF %% __SYSV_ADMINISTERED_SYSTEMS %%

+FIELD struct pkginfo | pkginfo_struct {
    char *pkginst ;
    char *name ;
    char *arch ;
    char *version ;
    char *basedir ;
    char *catg ;
    char *status ;
} ;

+CONST int PI_INSTALLED, PI_PARTIAL, PI_UNKNOWN, PI_SPOOLED ;

+EXP (extern) char *pkgdir ;
+FUNC int pkginfo ( struct pkginfo *, const char *, const char *,
		    const char * ) ;
+FUNC char *pkgparam ( const char *, const char * ) ;

+ENDIF
+ENDIF
