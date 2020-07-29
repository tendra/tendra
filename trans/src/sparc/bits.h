/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
