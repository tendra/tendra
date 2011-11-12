/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/szs_als.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: szs_als.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/09/05  16:27:29  pwe
 * alloca alignment is 64, not 32
 *
 * Revision 1.2  1996/01/23  10:31:29  john
 * Changed frame alignment
 *
 * Revision 1.1.1.1  1995/03/13  10:18:58  john
 * Entered into CVS
 *
 * Revision 1.3  1995/02/28  14:02:27  john
 * Added 64 bit sizes & alignments
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:45  djch
 * Initial revision
 *
 * Revision 1.3  93/09/27  14:57:08  14:57:08  ra (Robert Andrews)
 * Correct LDOUBLE_BITS to 113.
 * 
 * Revision 1.2  93/08/13  14:47:25  14:47:25  ra (Robert Andrews)
 * Define DOUBLE_SZ according to the value of use_long_double.
 * 
 * Revision 1.1  93/06/24  14:59:31  14:59:31  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef SZS_ALS_INCLUDED
#define SZS_ALS_INCLUDED


/*
    BASIC SIZES AND ALIGNMENTS
*/

#define TOP_SZ			( ( long ) 0 )
#define TOP_ALIGN		const_al1

#define PROC_SZ			( ( long ) 32 )
#define PROC_ALIGN		const_al32

#define LLVALUE_SZ		( ( long ) 32 )
#define LLVALUE_ALIGN		const_al32

#define PTR_SZ			( ( long ) 32 )
#define PTR_ALIGN		const_al32
#define PTRBIT_SZ		( ( long ) 32 )

#define OFFSET_SZ		( ( long ) 32 )
#define OFFSET_ALIGN		const_al32

#define BF_ALIGN		const_al1
#define STRUCT_ALIGN		const_al8

#define SHREAL_SZ		( ( long ) 32 )
#define SHREAL_ALIGN		const_al32

#define REAL_SZ			( ( long ) 64 )
#define REAL_ALIGN		const_al64

#if use_long_double
#define DOUBLE_SZ		( ( long ) 128 )
#else
#define DOUBLE_SZ		( ( long ) 64 )
#endif
#define DOUBLE_ALIGN		const_al64

#define UCHAR_SZ		( ( long ) 8 )
#define UCHAR_ALIGN		const_al8

#define SCHAR_SZ		( ( long ) 8 )
#define SCHAR_ALIGN		const_al8

#define UWORD_SZ		( ( long ) 16 )
#define UWORD_ALIGN		const_al16

#define SWORD_SZ		( ( long ) 16 )
#define SWORD_ALIGN		const_al16

#define ULONG_SZ		( ( long ) 32 )
#define ULONG_ALIGN		const_al32

#define U64_SZ			( ( long ) 64 )
#define U64_ALIGN		const_al32

#define S64_SZ			( ( long ) 64 )
#define S64_ALIGN		const_al32

#define SLONG_SZ		( ( long ) 32 )
#define SLONG_ALIGN		const_al32

#define BF_STORE_UNIT		( ( long ) 32 )
#define MAX_BF_SIZE		const_al32

#define ALLOCA_ALIGN		const_al64
#define FRAME_ALIGN		const_al64
#define VAR_PARAM_ALIGN		const_al32
#define CODE_ALIGN		const_al32
#define MIN_PAR_ALIGNMENT	const_al32

/*
    FLOATING POINT MANTISSA SIZES
*/

#define FLOAT_BITS		24
#define DOUBLE_BITS		53
#define LDOUBLE_BITS		113


#endif /* SZS_ALS_INCLUDED */
