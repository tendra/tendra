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
**		INT64_types.h
**
**  This file defines both signed and unsigned types
**  to be used for 64-bit integer arithmetic in terms
**  of generic 32-bit integer types.
**
**  In addition, macros are provided to extract the hi-
**  and low-32 bits of data stored using these types.
**
*/

#ifndef __INT64_types_h
#define __INT64_types_h

/*  Define the generic 32-bit signed and unsigned types  */

#ifdef NATIVE_INT64
typedef int INT32;
typedef unsigned int UINT32;
#else
typedef long INT32;
typedef unsigned long UINT32;
#endif


/*  Define the new types for 64-bit integers */

/* Installers expect lo32 to be first, and hi32 to be second */

typedef struct {
    UINT32	lo32;
    INT32	hi32;
} INT64;

typedef struct {
    UINT32	lo32;
    UINT32	hi32;
} UINT64;


/*
**  'TDF_INT64' is a type which reflects the fact that both signed
**  and unsigned integers are stored in the same way internally,
**  and that many of the arithmetic operations (such as +, -, *, etc.)
**  do not need to know whether the integer is signed or unsigned.
**
**  This type allows prototyped functions to be defined in ANSI which
**  implement operations for both signed and unsigned integers.
**
*/

typedef union {
    INT64	s;
    UINT64	u;
} TDF_INT64;



/*  Macros for extracting the hi- and low-32 bits */

#define hi_32(X)		((X).s.hi32)
#define lo_32(X)		((X).s.lo32)

#define hi_u32(X)		((X).u.hi32)
#define lo_u32(X)		((X).u.lo32)



/*  Tokens to convert between the parameter representation  */
/*  of 64-bit integers, and the structure representation.   */

#define  LOCAL(X)  ((TDF_INT64) (X))
#define ULOCAL(X)  ((TDF_INT64) (X))

#define  PARAM(X) (( INT64) (X))
#define UPARAM(X) ((UINT64) (X))


/*  64-bit constants used in the calculations  */

TDF_INT64 const_0  = {{(INT32) 0, (UINT32) 0}}; /* intialising first element */
TDF_INT64 const_u0 = {{(INT32) 0, (UINT32) 0}}; /* i.e. a structure of type INT64 */
TDF_INT64 const_1  = {{(INT32) 1, (UINT32) 0}}; /* least-significant word comes first */
TDF_INT64 const_u1 = {{(INT32) 1, (UINT32) 0}};


#endif  /* ndef __INT64_types_h */
