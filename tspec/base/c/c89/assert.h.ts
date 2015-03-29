# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

$PROTECT = "";

+SUBSET "fail" := {

	+FUNC void __assert_aux(const char *, const char *, int, const char *);

	%%%
	#include <stdio.h>
	#include <stdlib.h>

	#define __assert_aux(e, f, n, l)                                  \
	    ((n) ? fprintf(stderr, "assertion failed: %s:%s():%d (%s)\n", \
	             (f), (n), (l), (e))                                  \
	         : fprintf(stderr, "assertion failed: %s:%d (%s)\n",      \
	             (f), (l), (e))                                       \
	         , abort())
	%%%

};

%% #undef assert %%

# 4.2.1.1 The assert macro
+IFDEF NDEBUG
+DEFINE assert.1(e) %% ((void) 0) %%;
+ELSE
+DEFINE assert.2(e) %% ((e) ? (void) 0 : __assert_aux(#e, __FILE__, 0, __LINE__)) %%;
+ENDIF

