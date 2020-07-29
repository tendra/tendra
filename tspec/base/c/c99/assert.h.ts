# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "assert.h.ts", "fail";

%% #undef assert %%

# 7.2.1.1 The assert macro
+IFDEF NDEBUG
+DEFINE assert.1(e) %% ((void)0) %%;
+ELSE
+DEFINE assert.2(e) %% ((e) ? (void) 0 : __assert_aux(#e, __FILE__, __func__, __LINE__)) %%;
+ENDIF

