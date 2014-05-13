# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# This is the "POSIX2 C-Language Binding" (CLB) Feature Group
# of XSH Issue 4 Version 2, "System Interfaces and Headers",
# which constitutes the C headers part of XPG4v2.
# Specified by X/Open as part of CAE. Document number C435,
# ISBN: 1-85912-037-7 published September 1994.

$UNIQUE = 1 ;
$VERSION = "2.7" ;

$INFO = "X/Open CAE XSH Issue 4 Version 2 - POSIX2 C-Language Binding";

+IMPLEMENT "cae/xsh4v2-clb", "fnmatch.h.ts" ;
+IMPLEMENT "cae/xsh4v2-clb", "glob.h.ts" ;
+IMPLEMENT "cae/xsh4v2-clb", "regex.h.ts" ;
+IMPLEMENT "cae/xsh4v2-clb", "wordexp.h.ts" ;

