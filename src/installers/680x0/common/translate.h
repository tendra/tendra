/*
    		 Crown Copyright (c) 1996
    
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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/translate.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: translate.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:00  ma
First version.

Revision 1.2  1997/09/25 06:45:38  ma
All general_proc tests passed

Revision 1.1.1.1  1997/03/14 07:50:16  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:59  john
 *
 * Revision 1.2  1996/07/05  14:28:15  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:18  john
 *
 * Revision 1.1  93/02/22  17:16:52  17:16:52  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


/*
    TRANSLATIONS BETWEEN OLD SPECIFICATION AND NEW
*/

#define  botsh			f_bottom
#define  topsh			f_top
#define  proksh			f_proc
#define  ptr_shape( X )		f_pointer ( f_alignment ( X ) )

#if 1

#define  is_offset( X )\
	( name ( sh ( X ) ) == offsethd && al2 ( sh ( X ) ) != 1 )
#else

#define is_offset(X)\
        (name(sh(X)) == offsethd && \
	 (((al2(sh(son(X))) == 1) && (al2(sh(bro(son(X))))!=1)) || \
	  ((al2(sh(son(X)))!=1) && (al2(sh(bro(son(X)))) == 1))))
#endif

#define  simple_exp( X )\
	getexp ( botsh, nilexp, 0, nilexp, nilexp, 0, L0, X )
