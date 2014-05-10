# $Id$

# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

# This is the "POSIX2 C-Language Binding" (CLB) Feature Group
# of XSH Issue 4, "System Interfaces and Headers",
# which constitutes the C headers part of XPG4.
# Specified by X/Open as part of CAE. Document number C202,
# ISBN: 1-872630-47-2 publushed July 1992.

$UNIQUE  = 1;
$VERSION = "2.6";
+BASE_API;

$INFO = "X/Open CAE XSH Issue 4 - POSIX2 C-Language Binding";

+IMPLEMENT "cae/xsh4-clb", "fnmatch.h.ts";
+IMPLEMENT "cae/xsh4-clb", "glob.h.ts";
+IMPLEMENT "cae/xsh4-clb", "regex.h.ts";
+IMPLEMENT "cae/xsh4-clb", "wordexp.h.ts";

