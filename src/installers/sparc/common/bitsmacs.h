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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/bitsmacs.h,v 1.1.1.1 1998/01/17 15:55:53 release Exp $
--------------------------------------------------------------------------
$Log: bitsmacs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1997/10/28  10:18:45  pwe
 * extra diags
 *
 * Revision 1.1.1.1  1995/03/13  10:18:27  john
 * Entered into CVS
 *
 * Revision 1.6  1994/11/28  13:51:43  djch
 * removed subvar on ic's advice.
 *
 * Revision 1.5  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.4  1994/05/25  14:18:21  djch
 * Added CREATE_instore_bits to shut up tcc
 *
 * Revision 1.3  1994/05/13  12:25:49  djch
 * Incorporates improvements from expt version
 * Remove redundant macros
 *
 * Revision 1.2  1994/05/03  15:01:06  djch
 * added inlined bit used in 3.0 common section
 *
 * Revision 1.3  93/08/27  11:21:13  11:21:13  ra (Robert Andrews)
 * Changed SetRev etc to use pset, altered some whitespace.
 * 
 * Revision 1.2  93/07/08  18:18:31  18:18:31  ra (Robert Andrews)
 * Minor reformatting.
 * 
 * Revision 1.1  93/06/24  14:57:57  14:57:57  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef BITSMACS_INCLUDED
#define BITSMACS_INCLUDED


/*
    PROPERTIES FOR NEEDS
*/

#define morefix			0x0100
#define morefloat		0x0200
#define hasproccall		0x0400
#define usesproccall		0x0800	/* hasproccall << 1 */
#define anyproccall		0x0c00
#define long_result_bit		0x1000
#define has_result_bit		0x2000
#define regsused		0x0d00	/* composite */
#define fregsused		0x0e00	/* composite */
#define realresult_bit		0x4000
#define longrealresult_bit	0x8000
#define uses_res_reg_bit	0x0002
#define dont_optimise		0x0004


/*
    SPARC-SPECIFIC IDENT PROPERTIES
*/

#define inreg_bits		0x0800
#define infreg_bits		0x1000
#define inanyreg		0x1800
#define defer_bit		0x2000
#define notparreg		0x4000
#define notresreg		0x8000
#define sreguse			0x0200
#define inlined			0x0400

/*
    PROPERTIES OF REAL OPERATIONS
*/

#define SetRev( e )		pset ( e, 0x1000 )
#define IsRev( e )		ptst ( e, 0x1000 )
#define ClearRev( e )		pclr ( e, 0x1000 )

/*
    LABST PROPERTIES
*/

#define set_dg_labmark( e )	pset ( e, 0x800 )
#define dg_labmark( e )		ptst ( e, 0x800 )
#define clear_dg_labmark( e )	pclr ( e, 0x800 )


/*
    MISCELLANEOUS MACROS
*/


#endif /* BITSMACS_INCLUDED */
