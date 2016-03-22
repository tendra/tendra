/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */
    
#ifndef LOCAL_AL_H
#define LOCAL_AL_H

#include <construct/aldefs.h>

/*
    SIZES AND ALIGNMENTS OF BASIC SHAPES
*/

#define  TOP_SZ		 0		/* size of void */
#define  TOP_ALIGN	 const_al1	/* alignment of void */

#define  SCHAR_SZ	 8		/* size of signed char */
#define  SCHAR_ALIGN	 const_al8	/* alignment of signed char */
#define  UCHAR_SZ	 8		/* size of unsigned char */
#define  UCHAR_ALIGN	 const_al8	/* alignment of unsigned char */

#define  SWORD_SZ	 16		/* size of signed short */
#define  SWORD_ALIGN	 const_al16	/* alignment of signed short */
#define  UWORD_SZ	 16		/* size of unsigned short */
#define  UWORD_ALIGN	 const_al16	/* alignment of unsigned short */

#define  SLONG_SZ	 32		/* size of signed long */
#define  SLONG_ALIGN	 const_al16	/* alignment of signed long */
#define  ULONG_SZ	 32		/* size of unsigned long */
#define  ULONG_ALIGN	 const_al16	/* alignment of unsigned long */

#define  SHREAL_SZ	 32		/* size of float */
#define  SHREAL_ALIGN	 const_al16	/* alignment of float */

#define  REAL_SZ	 64		/* size of double */
#define  REAL_ALIGN	 const_al16	/* alignment of double */

#define  DOUBLE_SZ	 64		/* size of long double */
#define  DOUBLE_ALIGN	 const_al16	/* alignment of long double */

#define  STRUCT_ALIGN	 const_al16	/* alignment of struct */

#define  BF_ALIGN	 const_al1	/* alignment of bit */
#define  BF_STORE_UNIT	 16		/* alignment of bitfield */
#define  MAX_BF_SIZE_CC	 const_al32	/* cc bitfield rule */
#define  MAX_BF_SIZE_GCC const_al64	 /* gcc bitfield rule */
extern alignment MAX_BF_SIZE ;	 	/* bitfield rule */

#define  PROC_SZ	 32		/* size of ptr proc */
#define  PROC_ALIGN	 const_al16	/* alignment of ptr proc */

#define  PTR_SZ		 32			/* size of pointer */
#define  PTRBIT_SZ	 (abi == ABI_SUNOS ? 32 : 64)	/* size of ptr bit */
#define  PTR_ALIGN	 const_al16		/* alignment of pointer */

#define  OFFSET_SZ	 32		/* size of offset */
#define  OFFSET_ALIGN	 const_al16	/* alignment of offset */

#define  LLVALUE_SZ	 32		/* size of label value */
#define  LLVALUE_ALIGN	 const_al16	/* alignment of label value */

#define  ALLOCA_ALIGN	 (abi == ABI_SUNOS ? const_al32 : const_al16)
#define  FRAME_ALIGN	 (abi == ABI_SUNOS ? const_al32 : const_al16)
#define  VAR_PARAM_ALIGN (abi == ABI_SUNOS ? const_al32 : const_al16)
#define  CODE_ALIGN	 const_al16

#define  PARAM_ALIGN	 (abi == ABI_SUNOS ? 32 : 16)	/* alignment of proc arguments */
#define  STACK_ALIGN	 16				/* alignment of stack objects */
#define  DBL_ALIGN	 16				/* alignment of doubles */

#define MIN_PAR_ALIGNMENT (abi == ABI_SUNOS ? const_al32 : const_al16)

#define U64_SZ 64
#define U64_ALIGN const_al16

#define S64_SZ 64
#define S64_ALIGN const_al16


/*
    SIZES OF MANTISSAS OF FLOATING POINT NUMBERS
*/

#define  FLOAT_BITS	 24		/* mantissa size for float */
#define  DOUBLE_BITS	 53		/* mantissa size for double */
#define  LDOUBLE_BITS	 53		/* mantissa size for long double */


#endif
