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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/szs_als.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: szs_als.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/11/13 08:27:19  ma
All avs test passed (except add_to_ptr).

Revision 1.1.1.1  1997/10/13 12:42:59  ma
First version.

Revision 1.3  1997/10/13 08:50:09  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.2  1997/09/25 06:45:33  ma
All general_proc tests passed

Revision 1.1.1.1  1997/03/14 07:50:18  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:58  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:17  john
 *
 * Revision 1.2  93/04/19  13:37:07  13:37:07  ra (Robert Andrews)
 * Representation of alignments has changed.  New alignments required
 * by March93 spec.
 * 
 * Revision 1.1  93/02/22  17:16:41  17:16:41  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef SZS_ALS_INCLUDED
#define SZS_ALS_INCLUDED

/*
    SIZES AND ALIGNMENTS OF BASIC SHAPES
*/

#ifdef SUN

#define  TOP_SZ		 L0		/* size of void */
#define  TOP_ALIGN	 const_al1	/* alignment of void */

#define  SCHAR_SZ	 L8		/* size of signed char */
#define  SCHAR_ALIGN	 const_al8	/* alignment of signed char */
#define  UCHAR_SZ	 L8		/* size of unsigned char */
#define  UCHAR_ALIGN	 const_al8	/* alignment of unsigned char */

#define  SWORD_SZ	 L16		/* size of signed short */
#define  SWORD_ALIGN	 const_al16	/* alignment of signed short */
#define  UWORD_SZ	 L16		/* size of unsigned short */
#define  UWORD_ALIGN	 const_al16	/* alignment of unsigned short */

#define  SLONG_SZ	 L32		/* size of signed long */
#define  SLONG_ALIGN	 const_al16	/* alignment of signed long */
#define  ULONG_SZ	 L32		/* size of unsigned long */
#define  ULONG_ALIGN	 const_al16	/* alignment of unsigned long */

#define  SHREAL_SZ	 L32		/* size of float */
#define  SHREAL_ALIGN	 const_al16	/* alignment of float */

#define  REAL_SZ	 L64		/* size of double */
#define  REAL_ALIGN	 const_al16	/* alignment of double */

#define  DOUBLE_SZ	 L64		/* size of long double */
#define  DOUBLE_ALIGN	 const_al16	/* alignment of long double */

#define  STRUCT_ALIGN	 const_al16	/* alignment of struct */

#define  BF_ALIGN	 const_al1	/* alignment of bit */
#define  BF_STORE_UNIT	 L16		/* alignment of bitfield */
#define  MAX_BF_SIZE_CC	 const_al32	/* cc bitfield rule */
#define  MAX_BF_SIZE_GCC const_al64	 /* gcc bitfield rule */
extern alignment MAX_BF_SIZE ;	 	/* bitfield rule */

#define  PROC_SZ	 L32		/* size of ptr proc */
#define  PROC_ALIGN	 const_al16	/* alignment of ptr proc */

#define  PTR_SZ		 L32		/* size of pointer */
#define  PTRBIT_SZ	 L32		/* size of ptr bit */
#define  PTR_ALIGN	 const_al16	/* alignment of pointer */

#define  OFFSET_SZ	 L32		/* size of offset */
#define  OFFSET_ALIGN	 const_al16	/* alignment of offset */

#define  LLVALUE_SZ	 L32		/* size of label value */
#define  LLVALUE_ALIGN	 const_al16	/* alignment of label value */

#define  ALLOCA_ALIGN	 const_al32
#define  FRAME_ALIGN	 const_al32
#define  VAR_PARAM_ALIGN const_al32
#define  CODE_ALIGN	 const_al16

#define  PARAM_ALIGN	 L32		/* alignment of proc arguments */
#define  STACK_ALIGN	 L16		/* alignment of stack objects */
#define  DBL_ALIGN	 L16		/* alignment of doubles */

#define MIN_PAR_ALIGNMENT const_al32

#define U64_SZ ((long)64)
#define U64_ALIGN const_al16

#define S64_SZ ((long)64)
#define S64_ALIGN const_al16


#else

#define  TOP_SZ		 L0		/* size of void */
#define  TOP_ALIGN	 const_al1	/* alignment of void */

#define  SCHAR_SZ	 L8		/* size of signed char */
#define  SCHAR_ALIGN	 const_al8	/* alignment of signed char */
#define  UCHAR_SZ	 L8		/* size of unsigned char */
#define  UCHAR_ALIGN	 const_al8	/* alignment of unsigned char */

#define  SWORD_SZ	 L16		/* size of signed short */
#define  SWORD_ALIGN	 const_al16	/* alignment of signed short */
#define  UWORD_SZ	 L16		/* size of unsigned short */
#define  UWORD_ALIGN	 const_al16	/* alignment of unsigned short */

#define  SLONG_SZ	 L32		/* size of signed long */
#define  SLONG_ALIGN	 const_al16	/* alignment of signed long */
#define  ULONG_SZ	 L32		/* size of unsigned long */
#define  ULONG_ALIGN	 const_al16	/* alignment of unsigned long */

#define  SHREAL_SZ	 L32		/* size of float */
#define  SHREAL_ALIGN	 const_al16	/* alignment of float */

#define  REAL_SZ	 L64		/* size of double */
#define  REAL_ALIGN	 const_al16	/* alignment of double */

#define  DOUBLE_SZ	 L64		/* size of long double */
#define  DOUBLE_ALIGN	 const_al16	/* alignment of long double */

#define  STRUCT_ALIGN	 const_al16	/* alignment of struct */

#define  BF_ALIGN	 const_al1	/* alignment of bit */
#define  BF_STORE_UNIT	 L16		/* alignment of bitfield */
#define  MAX_BF_SIZE_CC	 const_al32	/* cc bitfield rule */
#define  MAX_BF_SIZE_GCC const_al64	 /* gcc bitfield rule */
extern alignment MAX_BF_SIZE ;	 	/* bitfield rule */

#define  PROC_SZ	 L32		/* size of ptr proc */
#define  PROC_ALIGN	 const_al16	/* alignment of ptr proc */

#define  PTR_SZ		 L32		/* size of pointer */
#define  PTRBIT_SZ	 L64		/* size of ptr bit */
#define  PTR_ALIGN	 const_al16	/* alignment of pointer */

#define  OFFSET_SZ	 L32		/* size of offset */
#define  OFFSET_ALIGN	 const_al16	/* alignment of offset */

#define  LLVALUE_SZ	 L32		/* size of label value */
#define  LLVALUE_ALIGN	 const_al16	/* alignment of label value */

#define  ALLOCA_ALIGN	 const_al16
#define  FRAME_ALIGN	 const_al16
#define  VAR_PARAM_ALIGN const_al16
#define  CODE_ALIGN	 const_al16

#define  PARAM_ALIGN	 L16		/* alignment of proc arguments */
#define  STACK_ALIGN	 L16		/* alignment of stack objects */
#define  DBL_ALIGN	 L16		/* alignment of doubles */

#define MIN_PAR_ALIGNMENT const_al16

#define U64_SZ ((long)64)
#define U64_ALIGN const_al16

#define S64_SZ ((long)64)
#define S64_ALIGN const_al16

#endif

/*
    SIZES OF MANTISSAS OF FLOATING POINT NUMBERS
*/

#define  FLOAT_BITS	 24		/* mantissa size for float */
#define  DOUBLE_BITS	 53		/* mantissa size for double */
#define  LDOUBLE_BITS	 53		/* mantissa size for long double */


/*
    MAXIMUM EXPONENT ALLOWED IN FLOATING-POINT CONSTANTS
*/

extern int target_dbl_maxexp ;

#endif
