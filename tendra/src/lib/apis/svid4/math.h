#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
+USE "svid3", "", "config" ;
+IMPLEMENT "xpg3", "math.h" ;

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
