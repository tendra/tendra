# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix", "fcntl.h.ts" ;

+SUBSET "o_sync" := {
    +USE "xpg3", "sys/types.h.ts" (?!) ;
    +CONST int O_SYNC ;
} ;
