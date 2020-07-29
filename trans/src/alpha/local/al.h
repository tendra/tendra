/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCAL_AL_H
#define LOCAL_AL_H

/*
** This file provides the sizes and aligments required for the alpha 
** installer.  This information is used in the common part of the installer.
**
*/

#define TOP_SZ 0
#define TOP_ALIGN const_al1

#define PROC_SZ 64		
#define PROC_ALIGN const_al64

#define LLVALUE_SZ 64
#define LLVALUE_ALIGN const_al64

#define PTR_SZ 64
#define PTR_ALIGN const_al64
#define PTRBIT_SZ 64

#define OFFSET_SZ 64
#define OFFSET_ALIGN const_al64

#define BF_ALIGN const_al1

#define STRUCT_ALIGN const_al8

#define SHREAL_SZ 32
#define SHREAL_ALIGN const_al32

#define REAL_SZ 64
#define REAL_ALIGN const_al64

#define DOUBLE_SZ 64
#define DOUBLE_ALIGN const_al64

#define UCHAR_SZ 8
#define UCHAR_ALIGN const_al8

#define SCHAR_SZ 8
#define SCHAR_ALIGN const_al8

#define UWORD_SZ 16
#define UWORD_ALIGN const_al16

#define SWORD_SZ 16
#define SWORD_ALIGN const_al16

#define SLONG_SZ 32
#define SLONG_ALIGN const_al32
#define ULONG_SZ 32
#define ULONG_ALIGN const_al32

#define U64_SZ	64
#define U64_ALIGN const_al64
#define S64_SZ	64
#define S64_ALIGN const_al64

#define BF_STORE_UNIT 64
#define MAX_BF_SIZE const_al64		/* guess */

#define FLOAT_BITS 24
#define DOUBLE_BITS 53
#define LDOUBLE_BITS 64

#define MIN_PAR_ALIGNMENT const_al64

#define ALLOCA_ALIGN const_al32		/* leave at 32 for the moment */
#define FRAME_ALIGN const_al64
#define VAR_PARAM_ALIGN const_al64
#define CODE_ALIGN const_al32

#endif

