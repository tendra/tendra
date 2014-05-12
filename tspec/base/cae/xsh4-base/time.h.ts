# $Id$

# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "time.h.ts", "time_t" ;
+IMPLEMENT "cae/xpg3", "time.h.ts" ;

/*
 * TODO: "Although the value of CLOCKS_PER_SEC is required to be 1 million on all XSI-conformant
 * systems, it may be variable on other systems and it should not be assumed that
 * CLOCKS_PER_SEC is a compile-time constant."
 */
# +DEFINE CLOCKS_PER_SEC 1000000;

