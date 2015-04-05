# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# This is ANSI C, as defined in X3.159 by X3J11,
# developed by the the X3J11 Technical Committee.
# X3.159 is commonly known as C89, republished as
# ISO/IEC 9899:1990 which is commonly known as C90.

$UNIQUE  = 1;
$VERSION = "2.6";
+BASE_API;

$INFO = "ANSI X3.159 / ISO/IEC 9899:1990 - Hosted";

# C99 onwards qualify several things with restrict, but are otherwise identical
# to their specifications for earlier standards. Rather than fragmenting these
# into subsets and overriding those to introduce restrict, a definition is made
# conditionally here. This helps keep related functions together, especially for
# headers which are already complex.
#
# The downside is of course that it seems inappropriate to have "~restrict"
# appear in C89 headers, even if it expands out to nothing. But the benefit is
# that it makes both C89 and C99 headers an awful lot simpler.
+SUBSET "restrict" := {
	+IF %% __STDC_VERSION__ >= 199901L %%
	+DEFINE ~restrict.1 %% restrict %%;
	+ELSE
	+DEFINE ~restrict.2 %%          %%;
	+ENDIF
};

# 4.1.2 Standard headers
+IMPLEMENT "c/c89", "assert.h.ts";
+IMPLEMENT "c/c89", "ctype.h.ts";
+IMPLEMENT "c/c89", "errno.h.ts";
+IMPLEMENT "c/c89", "float.h.ts";
+IMPLEMENT "c/c89", "limits.h.ts";
+IMPLEMENT "c/c89", "locale.h.ts";
+IMPLEMENT "c/c89", "math.h.ts";
+IMPLEMENT "c/c89", "setjmp.h.ts";
+IMPLEMENT "c/c89", "signal.h.ts";
+IMPLEMENT "c/c89", "stdarg.h.ts";
+IMPLEMENT "c/c89", "stddef.h.ts";
+IMPLEMENT "c/c89", "stdio.h.ts";
+IMPLEMENT "c/c89", "stdlib.h.ts";
+IMPLEMENT "c/c89", "string.h.ts";
+IMPLEMENT "c/c89", "time.h.ts";

