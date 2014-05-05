# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+SUBSET "values" := {
    +IMPLEMENT "posix", "limits.h.ts" ;
    +IMPLEMENT "c/c89", "stdio.h.ts", "tmp_max" (!?) ;

    +CONST int LONG_BIT, NL_ARGMAX, NL_LANGMAX, NL_MSGMAX, NL_NMAX ;
    +CONST int NL_SETMAX, NL_TEXTMAX, NZERO, WORD_BIT ;

    +IF 0
    /* This value is optional */
    +CONST int PASS_MAX ;
    +ENDIF
} ;

+IMPLEMENT "c/c89", "float.h.ts", "xpg3_ranges" (!?) ;
