# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "xpg3", "stdio.h.ts" ;
+CONST char *P_tmpdir ;
+SUBSET "optopt" := { +EXP (extern) int optopt ; } ;
