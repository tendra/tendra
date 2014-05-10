# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# This is ISO C, as defined in ISO/IEC 9899:1990 and
# commonly known as C90.
#
# C90 extends ANSI X3.159 C89, adding wint_t and friends.

$UNIQUE  = 1;
$VERSION = "2.6";
+BASE_API;

$INFO = "ISO/IEC 9899:1990 - Hosted";

# these inherit as-is from c89
+IMPLEMENT "c/c90", "assert.h.ts";
+IMPLEMENT "c/c90", "ctype.h.ts";
+IMPLEMENT "c/c90", "float.h.ts";
+IMPLEMENT "c/c90", "limits.h.ts";
+IMPLEMENT "c/c90", "locale.h.ts";
+IMPLEMENT "c/c90", "math.h.ts";
+IMPLEMENT "c/c90", "setjmp.h.ts";
+IMPLEMENT "c/c90", "signal.h.ts";
+IMPLEMENT "c/c90", "stdarg.h.ts";
+IMPLEMENT "c/c90", "stddef.h.ts";
+IMPLEMENT "c/c90", "stdio.h.ts";
+IMPLEMENT "c/c90", "stdlib.h.ts";
+IMPLEMENT "c/c90", "string.h.ts";
+IMPLEMENT "c/c90", "time.h.ts";

# specific to c90
+IMPLEMENT "c/c90", "errno.h.ts";
+IMPLEMENT "c/c90", "iso646.h.ts";
+IMPLEMENT "c/c90", "wchar.h.ts";
+IMPLEMENT "c/c90", "wctype.h.ts";

