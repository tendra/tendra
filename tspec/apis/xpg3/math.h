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
+IMPLEMENT "ansi", "math.h" ;

+EXP double MAXFLOAT ;
+CONST double M_1_PI, M_2_PI, M_2_SQRTPI, M_E, M_LN2, M_LN10 ;
+CONST double M_LOG2E, M_LOG10E, M_PI, M_PI_2, M_PI_4, M_SQRT2, M_SQRT1_2 ;

+FUNC double erf ( double ) ;
+FUNC double erfc ( double ) ;
+FUNC double gamma ( double ) ;
+FUNC double hypot ( double, double ) ;
+FUNC int isnan ( double ) ;
+FUNC double j0 ( double ) ;
+FUNC double j1 ( double ) ;
+FUNC double jn ( int, double ) ;
+FUNC double lgamma ( double ) ;
+FUNC double y0 ( double ) ;
+FUNC double y1 ( double ) ;
+FUNC double yn ( int, double ) ;

+EXP (extern) int signgam ;
