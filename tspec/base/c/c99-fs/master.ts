# $Id$

# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

$PROTECT = "";

$UNIQUE  = 1;
$VERSION = "2.6";
+BASE_API;

$INFO = "ISO/IEC 9899:1999+TC1+TC2+TC3 - Freestanding";

+IMPLEMENT "c/c99-fs", "dummy.ts";

# 4.6
+IMPLEMENT "c/c99-fs", "float.h.ts";
+IMPLEMENT "c/c99-fs", "iso646.h.ts";
+IMPLEMENT "c/c99-fs", "limits.h.ts";
+IMPLEMENT "c/c99-fs", "stdarg.h.ts";
+IMPLEMENT "c/c99-fs", "stdbool.h.ts";
+IMPLEMENT "c/c99-fs", "stddef.h.ts";
+IMPLEMENT "c/c99-fs", "stdint.h.ts";

