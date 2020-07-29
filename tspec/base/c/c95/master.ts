# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# This is ISO C, as defined in ISO/IEC 9899:1990 plus
# ISO/IEC 9899/AMD1:1995 and commonly known as C94 or C95.
#
# AMD1 extends ISO/IEC 9899:1990, adding wint_t and friends.

$UNIQUE  = 1;
$VERSION = "2.6";
+BASE_API;

$INFO = "ISO/IEC 9899:1990 - Hosted + ISO/IEC 9899/AMD1:1995";

# these inherit as-is from c89
+IMPLEMENT "c/c95", "assert.h.ts";
+IMPLEMENT "c/c95", "ctype.h.ts";
+IMPLEMENT "c/c95", "float.h.ts";
+IMPLEMENT "c/c95", "limits.h.ts";
+IMPLEMENT "c/c95", "locale.h.ts";
+IMPLEMENT "c/c95", "math.h.ts";
+IMPLEMENT "c/c95", "setjmp.h.ts";
+IMPLEMENT "c/c95", "signal.h.ts";
+IMPLEMENT "c/c95", "stdarg.h.ts";
+IMPLEMENT "c/c95", "stddef.h.ts";
+IMPLEMENT "c/c95", "stdio.h.ts";
+IMPLEMENT "c/c95", "stdlib.h.ts";
+IMPLEMENT "c/c95", "string.h.ts";
+IMPLEMENT "c/c95", "time.h.ts";

# specific to c95
+IMPLEMENT "c/c95", "errno.h.ts";
+IMPLEMENT "c/c95", "iso646.h.ts";
+IMPLEMENT "c/c95", "wchar.h.ts";
+IMPLEMENT "c/c95", "wctype.h.ts";

