# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$LINKAGE = "C++" ;
$NAMESPACE = "std" ;
+USE ("c/c95"), "math.h.ts" ;

%%
float abs ( float ) ;
float acos ( float ) ;
float asin ( float ) ;
float atan ( float ) ;
float atan2 ( float, float ) ;
float ceil ( float ) ;
float cos ( float ) ;
float cosh ( float ) ;
float exp ( float ) ;
float fabs ( float ) ;
float floor ( float ) ;
float fmod ( float, float ) ;
float frexp ( float, int * ) ;
float modf ( float, float * ) ;
float ldexp ( float, int ) ;
float log ( float ) ;
float log10 ( float ) ;
float pow ( float, float ) ;
float pow ( float, int ) ;
float sin ( float ) ;
float sinh ( float ) ;
float sqrt ( float ) ;
float tan ( float ) ;
float tanh ( float ) ;

double abs ( double ) ;
double pow ( double, int ) ;

long double abs ( long double ) ;
long double acos ( long double ) ;
long double asin ( long double ) ;
long double atan ( long double ) ;
long double atan2 ( long double, long double ) ;
long double ceil ( long double ) ;
long double cos ( long double ) ;
long double cosh ( long double ) ;
long double exp ( long double ) ;
long double fabs ( long double ) ;
long double floor ( long double ) ;
long double fmod ( long double, long double ) ;
long double frexp ( long double, int * ) ;
long double modf ( long double, long double * ) ;
long double ldexp ( long double, int ) ;
long double log ( long double ) ;
long double log10 ( long double ) ;
long double pow ( long double, long double ) ;
long double pow ( long double, int ) ;
long double sin ( long double ) ;
long double sinh ( long double ) ;
long double sqrt ( long double ) ;
long double tan ( long double ) ;
long double tanh ( long double ) ;
%%
