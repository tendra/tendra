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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:07 $
$Revision: 1.1.1.1 $
$Log: szs_als.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:07  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/07/16  15:59:49  currie
 * alloca alignment
 *
Revision 1.1  1995/04/13 09:08:06  currie
Initial revision

***********************************************************************/

#define TOP_SZ (long)0
#define TOP_ALIGN const_al1

#define PROC_SZ (long)32
#define PROC_ALIGN const_al32

#define LLVALUE_SZ (long)32
#define LLVALUE_ALIGN const_al32

#define PTR_SZ (long)32
#define PTR_ALIGN const_al32
#define PTRBIT_SZ (long)64

#define OFFSET_SZ (long)32
#define OFFSET_ALIGN const_al32

#define BF_ALIGN const_al1

#define STRUCT_ALIGN const_al8

#define SHREAL_SZ (long)32
#define SHREAL_ALIGN const_al32

#define REAL_SZ (long)64
#define REAL_ALIGN const_al64

#define DOUBLE_SZ (long)64
#define DOUBLE_ALIGN const_al64

#define UCHAR_SZ (long)8
#define UCHAR_ALIGN const_al8

#define SCHAR_SZ (long)8
#define SCHAR_ALIGN const_al8

#define UWORD_SZ (long)16
#define UWORD_ALIGN const_al16

#define SWORD_SZ (long)16
#define SWORD_ALIGN const_al16

#define ULONG_SZ (long)32
#define ULONG_ALIGN const_al32

#define SLONG_SZ (long)32
#define SLONG_ALIGN const_al32

#define U64_ALIGN const_al32
#define U64_SZ (long)64

#define S64_ALIGN const_al32
#define S64_SZ (long)64


#define BF_STORE_UNIT (long)32
#define MAX_BF_SIZE const_al32

#define FLOAT_BITS 24
#define DOUBLE_BITS 53
#define LDOUBLE_BITS 64

#define MIN_PAR_ALIGNMENT const_al32
	/* This is the minimum alignment for parameters */

#define ALLOCA_ALIGN const_al64
#define FRAME_ALIGN const_al32
#define VAR_PARAM_ALIGN const_al32
#define CODE_ALIGN const_al32
