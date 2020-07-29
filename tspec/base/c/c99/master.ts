# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

# This is ISO C, as defined in ISO/IEC 9899:1999
# incorporating TC1, TC2 and TC3,
# developed by the the WG14 Technical Committee.
# ISO/IEC 9899:1999 is commonly known as C99.

$UNIQUE  = 1;
$VERSION = "2.6";
+BASE_API;

$INFO = "ISO/IEC 9899:1999+TC1+TC2+TC3 - Hosted";

# 7.1.2 Standard headers
+IMPLEMENT "c/c99", "assert.h.ts";
+IMPLEMENT "c/c99", "complex.h.ts";
+IMPLEMENT "c/c99", "ctype.h.ts";
+IMPLEMENT "c/c99", "errno.h.ts";
+IMPLEMENT "c/c99", "fenv.h.ts";
+IMPLEMENT "c/c99", "float.h.ts";
+IMPLEMENT "c/c99", "inttypes.h.ts";
+IMPLEMENT "c/c99", "iso646.h.ts";
+IMPLEMENT "c/c99", "limits.h.ts";
+IMPLEMENT "c/c99", "locale.h.ts";
+IMPLEMENT "c/c99", "math.h.ts";
+IMPLEMENT "c/c99", "setjmp.h.ts";
+IMPLEMENT "c/c99", "signal.h.ts";
+IMPLEMENT "c/c99", "stdarg.h.ts";
+IMPLEMENT "c/c99", "stdbool.h.ts";
+IMPLEMENT "c/c99", "stddef.h.ts";
+IMPLEMENT "c/c99", "stdint.h.ts";
+IMPLEMENT "c/c99", "stdio.h.ts";
+IMPLEMENT "c/c99", "stdlib.h.ts";
+IMPLEMENT "c/c99", "string.h.ts";
+IMPLEMENT "c/c99", "tgmath.h.ts";
+IMPLEMENT "c/c99", "time.h.ts";
+IMPLEMENT "c/c99", "wchar.h.ts";
+IMPLEMENT "c/c99", "wctype.h.ts";

