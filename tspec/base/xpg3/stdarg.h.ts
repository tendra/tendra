# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IFDEF __JUST_XPG3
%% #error stdarg.h is not in XPG3 %%
+ELSE
+IMPLEMENT "c/c89", "stdarg.h.ts" ;
+ENDIF
