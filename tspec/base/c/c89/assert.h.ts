# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

$PROTECT = "";

+SUBSET "fail" := {

	+FUNC void __assert_aux(const char *exp,
		const char *file, const char *func, int line);

	%%%
	#include <stdio.h>
	#include <stdlib.h>

	#define __assert_aux(exp, file, func, line)                          \
	    ((func) ? fprintf(stderr, "assertion failed: %s:%s():%d (%s)\n", \
	                (file), (func), (line), (exp))                       \
	            : fprintf(stderr, "assertion failed: %s:%d (%s)\n",      \
	                (file), (line), (exp))                               \
	            , abort())
	%%%

};

%% #undef assert %%

# 4.2.1.1 The assert macro
+IFDEF NDEBUG
+DEFINE assert.1(exp) %% ((void) 0) %%;
+ELSE
+DEFINE assert.2(exp) %% ((exp) ? (void) 0 : __assert_aux(#exp, __FILE__, 0, __LINE__)) %%;
+ENDIF

