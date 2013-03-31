/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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

#define DOUBLE_SZ		( use_long_double ? ( long ) 128 : ( long ) 64 )
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
