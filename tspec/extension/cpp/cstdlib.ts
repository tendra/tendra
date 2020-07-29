# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$LINKAGE = "C++" ;
$NAMESPACE = "std" ;
+USE ("c/c95"), "stdlib.h.ts" ;

%%
long abs ( long ) ;
ldiv_t div ( long, long ) ;
%%

%%
extern "C" {
#undef atexit
%%
+IFNDEF __CPP_NATIVE_ATEXIT
+FUNC int atexit.1 | "~cpp.destr.atexit" ( void (*) ( void ) ) ;
+ENDIF
%%
}
%%
