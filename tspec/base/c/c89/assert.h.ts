# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

$PROTECT = "";

+SUBSET "fail" := {

	+FUNC void __assert_aux(const char *, const char *, int);

	%%%
	#include <stdio.h>
	#include <stdlib.h>

	/* Provide token definition here */
	#define __assert_aux(e, f, l) \
		(fprintf(stderr, "assertion failed: %s, file %s, line %d\n", \
			(e), (f), (l) ), abort())
	%%%

};

%% #undef assert %%

# 4.2.1.1 The assert macro
+IFDEF NDEBUG
+DEFINE assert.1(e) %% ((void) 0) %%;
+ELSE
+DEFINE assert.2(e) %% ((e) ? (void) 0 : __assert_aux(#e, __FILE__, __LINE__)) %%;
+ENDIF

