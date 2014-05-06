# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Main body from posix1
+IMPLEMENT "posix/posix1", "unistd.h.ts" ;
+IMPLEMENT "posix/posix", "unistd.h.ts", "getopt" ;

+CONST int _CS_PATH, _POSIX2_C_VERSION, _SC_BC_BASE_MAX, _SC_BC_DIM_MAX ;
+CONST int _SC_BC_SCALE_MAX, _SC_BC_STRING_MAX, _SC_COLL_WEIGHTS_MAX ;
+CONST int _SC_EXPR_NEST_MAX, _SC_LINE_MAX, _SC_RE_DUP_MAX, _SC_2_VERSION ;
+CONST int _SC_2_C_DEV, _SC_2_FORT_DEV, _SC_2_FORT_RUN, _SC_2_LOCALEDEF ;
+CONST int _SC_2_SW_DEV ;

+FUNC size_t confstr ( int, char *, size_t ) ;
