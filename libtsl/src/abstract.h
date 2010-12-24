/*
    		 Crown Copyright (c) 1997, 1998
    
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
**		abstract.h
**
**  This file contains C #pragma statements which act
**  as the interface to the tokens defined in the file
**  abstract.pl.
*/

#if !defined(__INT64_API_h)
#define __INT64_API_h


/*  Define the generic 32-bit signed and unsigned types  */

#ifdef NATIVE_INT64
typedef int INT32;
typedef unsigned int UINT32;
#else
typedef long INT32;
typedef unsigned long UINT32;
#endif



/*  Define the widest floating variety - not possible in C  */

/*  The C Producer can't tokenise FLOATING_VARIETIES.  */



/*  Define the new types for 64-bit integers  */

#pragma token TYPE INT64 #
#pragma token TYPE UINT64 #
#pragma no_def INT64
#pragma no_def UINT64


/*  Are 64-bit integers are conceptually hi-word first ?  */

#if BIGENDIAN_INT64
struct _s {
    INT32	hi32;
    UINT32	lo32;
};
struct _u {
    UINT32	hi32;
    UINT32	lo32;
} u;

#else

struct _s {
    UINT32	lo32;
    INT32	hi32;
};
struct _u {
    UINT32	lo32;
    UINT32	hi32;
} u;
#endif  /* BIGENDIAN_INT64 */


typedef union {
   struct _s	s;
   struct _u	u;
   INT64	s64;
   UINT64	u64;
} TDF_INT64;

/*  Macros for extracting the high- and low-32 bits  */

#define hi_32(X)		((X).s.hi32)
#define lo_32(X)		((X).s.lo32)

#define hi_u32(X)		((X).u.hi32)
#define lo_u32(X)		((X).u.lo32)

#define  PARAM(X)		((X).s64)
#define UPARAM(X)		((X).u64)



/*  64-bit constants used in the implementation  */

#pragma token EXP rvalue : TDF_INT64 : const_0  #
#pragma token EXP rvalue : TDF_INT64 : const_u0 #
#pragma token EXP rvalue : TDF_INT64 : const_1  #
#pragma token EXP rvalue : TDF_INT64 : const_u1 #


#endif  /* !defined(__INT64_API_h) */
