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
**		abstract.ph
**
**  This file contains PL_TDF token declarations which
**  act as the interface to the tokens defined in the
**  file abstract.pl.
*/


/*  Define the generic 32-bit signed and unsigned types  */

Tokdec  ~INT32 : [] VARIETY;
Tokdec   INT32 : [] SHAPE;
Tokdec ~UINT32 : [] VARIETY;
Tokdec  UINT32 : [] SHAPE;


/*  Define the new types for 64-bit integers  */

Tokdec  INT64 : [] SHAPE;
Tokdec UINT64 : [] SHAPE;


/*  Define the widest floating variety - not possible in C  */

Tokdec ~BigFloat : [] FLOATING_VARIETY;
Tokdec  BigFloat : [] SHAPE;



/*  Macros for extracting the high- and low-32 bits      */
/*    (These necessarily differ from the C equivalents)  */

Tokdec TDF_INT64 : [] SHAPE;

Tokdec hi_32 : [EXP] EXP;
Tokdec lo_32 : [EXP] EXP;

Tokdec hi_u32 : [EXP] EXP;
Tokdec lo_u32 : [EXP] EXP;

Tokdec .hi_32 : [] EXP;
Tokdec .lo_32 : [] EXP;

Tokdec .hi_u32 : [] EXP;
Tokdec .lo_u32 : [] EXP;

Tokdec  PARAM : [EXP] EXP;
Tokdec UPARAM : [EXP] EXP;

Tokdec  .PARAM : [] EXP;
Tokdec .UPARAM : [] EXP;



/*  64-bit constants used in the implementation  */

Tokdec const_0  : [] EXP;
Tokdec const_u0 : [] EXP;
Tokdec const_1  : [] EXP;
Tokdec const_u1 : [] EXP;
