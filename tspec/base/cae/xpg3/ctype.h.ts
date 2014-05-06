# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix", "ctype.h.ts" ;

+FUNC int toascii ( int ) ;
+FUNC int isascii ( int ) ;
+MACRO int _toupper ( int ) ;
+MACRO int _tolower ( int ) ;
