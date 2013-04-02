/* $Id$ */

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
#define long_result_bit 	0x1000
#define has_result_bit		0x2000
#define regsused		0x0d00	/* composite */
#define fregsused		0x0e00	/* composite */
#define realresult_bit		0x4000
#define longrealresult_bit  	0x8000
#define uses_res_reg_bit 	0x0002
#define dont_optimise 		0x0004
#define uses2_bit 2

/*
    HPPA-SPECIFIC IDENT PROPERTIES
*/

#define inreg_bits 		0x0800
#define infreg_bits 		0x1000
#define inanyreg 		0x1800
#define defer_bit 		0x2000
#define notparreg 		0x4000
#define notresreg 		0x8000
#define sreguse 		0x0200
#define inlined			0x0200
/* #define subvar 			0x0100 */

/*
    PROPERTIES OF REAL OPERATIONS
*/

#define SetRev( e )		props ( e ) |= 0x1000
#define IsRev( e )		( props (e) & 0x1000 )
#define ClearRev( e )		props ( e ) &= ~0x1000


/*
    MISCELLANEOUS MACROS
*/

#define inlineassign		9
#define UNITWEIGHT		16.0


#endif /* BITSMACS_INCLUDED */

