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
$Log: szs_als.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/10/24  15:51:22  wfs
 * Added "~alloc_size" special token. Minor change to alloca_tag - only need
 * one word for storage of pointer. Major change to round_tag (rounding to
 * unsigned chars) in the fix of avs bug.
 *
 * Revision 1.2  1995/12/18  13:12:38  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:28:16  16:28:16  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:19:04  11:19:04  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:28:58  15:28:58  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:44:36  13:44:36  wfs (William Simmonds)
 * Initial revision
 * 
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
#define DOUBLE_ALIGN		const_al64

#else

#define DOUBLE_SZ		REAL_SZ
#define DOUBLE_ALIGN		REAL_ALIGN

#endif


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

#define SLONG_SZ		( ( long ) 32 )
#define SLONG_ALIGN		const_al32

#define U64_ALIGN const_al32
#define U64_SZ (long)64

#define S64_ALIGN const_al32
#define S64_SZ (long)64

#define BF_STORE_UNIT		( ( long ) 32 )
#define MAX_BF_SIZE		const_al32

#define ALLOCA_ALIGN		const_al64
#define FRAME_ALIGN		const_al32
#define VAR_PARAM_ALIGN		const_al32
#define CODE_ALIGN		const_al32
#define MIN_PAR_ALIGNMENT       const_al32

/*
    FLOATING POINT MANTISSA SIZES
*/

#define FLOAT_BITS		24
#define DOUBLE_BITS		53

#if use_long_double
#define LDOUBLE_BITS               113
#else
# define LDOUBLE_BITS		64
#endif

#endif /* SZS_ALS_INCLUDED */






