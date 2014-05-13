# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+USE "posix/posix", "sys/types.h.ts", "mode_t" ;

# CAE, Networking Services, Issue 4

+CONST int S_IFSOCK, S_IFMT ;

+MACRO int S_ISSOCK ( mode_t ) ;

