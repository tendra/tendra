# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

$PROTECT = "";

$UNIQUE  = 1;
$VERSION = "2.6";
+BASE_API;

$INFO = "ANSI X3.159 - Freestanding";

+IMPLEMENT "c/c89-fs", "dummy.ts";

# 1.7
+IMPLEMENT "c/c89-fs", "float.h.ts";
+IMPLEMENT "c/c89-fs", "limits.h.ts";
+IMPLEMENT "c/c89-fs", "stdarg.h.ts";
+IMPLEMENT "c/c89-fs", "stddef.h.ts";

