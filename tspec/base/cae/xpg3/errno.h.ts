# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix/posix", "errno.h.ts" ;

+SUBSET "enums" := {
	+IMPLEMENT "posix/posix", "errno.h.ts", "enums" ;
	+CONST int EIDRM, ENOMSG, ETXTBSY ;
} ;

+SUBSET "enums-notblk" := {
	+CONST int ENOTBLK ;
} ;

