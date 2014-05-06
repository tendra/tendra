# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IMPLEMENT "xpg3", "math.h.ts" ;

+FUNC double acosh ( double ) ;
+FUNC double asinh ( double ) ;
+FUNC double atanh ( double ) ;
+FUNC double cbrt ( double ) ;
+FUNC double logb ( double ) ;
+FUNC double nextafter ( double, double ) ;
+FUNC double scalb ( double, double ) ;

+FIELD struct exception {
    int type ;
    char *name ;
    double arg1 ;
    double arg2 ;
    double retval ;
} ;

+CONST int DOMAIN, SING, OVERFLOW, UNDERFLOW, TLOSS, PLOSS ;

+FUNC int matherr ( struct exception * ) ;
+FUNC double remainder ( double, double ) ;

+IF %% __SYSV_UPDATE %%
+FUNC int isnand ( double ) ;
+ENDIF
