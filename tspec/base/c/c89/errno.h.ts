# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# 4.1.3 Errors <errno.h>
+EXP lvalue int errno ;
+SUBSET "enums" := {
    +CONST int EDOM, ERANGE ;
} ;

