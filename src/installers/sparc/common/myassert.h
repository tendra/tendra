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
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/myassert.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: myassert.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:47  john
 * Entered into CVS
 *
 * Revision 1.3  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.2  1994/05/13  13:00:35  djch
 * Incorporates improvements from expt version
 * macros now give line and file name with ANSI preprocessors. assert_expr
 * added.
 *
 * Revision 1.1  1994/05/03  14:50:26  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:52  14:58:52  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef MYASSERT_INCLUDED
#define MYASSERT_INCLUDED

#include "comment.h"

#ifdef DO_ASSERT

#if FS_STDC_HASH
#define a_fail( s,l,f )	fail ( "Assertion '" s "' failed " #l " in " f )
#define a_fail1( s,l,f ) a_fail ( s,l,f)
#define assert( e )	if ( !( e ) ) a_fail1 ( #e, __LINE__ , __FILE__ )
#define assert_expr( e,v )	(( e ) ? (v) :\
				 (a_fail1 ( #e, __LINE__ , __FILE__ ), (v)))

#else

#define assert( e )	if ( !( e ) ) fail ( "Assertion failed" )
#define assert_expr(e,v)  ((e) ? (v) : (fail("expr assertion"), (v)))

#endif

#else /* DO_ASSERT */

#define assert( e )	( ( void ) 0 )
#define assert_expr(e,v) v

#endif /* DO_ASSERT */

#endif /* MYASSERT_INCLUDED */
