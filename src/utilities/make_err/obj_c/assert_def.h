/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.2)
*/

#ifndef ASSERT_DEF_H_INCLUDED
#define ASSERT_DEF_H_INCLUDED

/* Assertion function definitions */

#ifndef assert_errors
static void assert_errors
    PROTO_N ( ( s, fn, ln ) )
    PROTO_T ( CONST_S char *s X CONST_S char *fn X int ln )
{
    ( void ) fprintf ( stderr, "Assertion %s failed, %s, line %d.\n", s, fn, ln ) ;
    abort () ;
}
#endif

errors *check_null_errors
    PROTO_N ( ( p, fn, ln ) )
    PROTO_T ( errors *p X CONST_S char *fn X int ln )
{
    if ( p == NULL ) assert_errors ( "Null pointer", fn, ln ) ;
    return ( p ) ;
}

errors *check_tag_errors
    PROTO_N ( ( p, t, fn, ln ) )
    PROTO_T ( errors *p X unsigned t X CONST_S char *fn X int ln )
{
    p = check_null_errors ( p, fn, ln ) ;
    if ( p->ag_tag != t ) assert_errors ( "Union tag", fn, ln ) ;
    return ( p ) ;
}

errors *check_tag_etc_errors
    PROTO_N ( ( p, tl, tb, fn, ln ) )
    PROTO_T ( errors *p X unsigned tl X unsigned tb X CONST_S char *fn X int ln )
{
    p = check_null_errors ( p, fn, ln ) ;
    if ( p->ag_tag < tl || p->ag_tag >= tb ) {
	assert_errors ( "Union tag", fn, ln ) ;
    }
    return ( p ) ;
}

#endif
