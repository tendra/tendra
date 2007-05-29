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


/* CAPSULE B:
	This might be a capsule which defines how array descriptors are laid
	out - could vary from platform to platform - bound by TDF linking
	to capsules produced from Fortran.
*/

Struct Desc (BASE:Ptr Double, LB:Int, UB:Int,
		STRIDE:offset(alignment(Double), alignment(Double)));
/* Desc is a token giving the shape of of a 1-d array pointer;
	BASE is token which extracts the base pointer from a Desc EXP
	.BASE is the offset of the base pointer from the start of a Desc
	etc for LB,UB and STRIDE
*/ 

Tokdef SIZE = [e:EXP]EXP 
	( STRIDE[e] .* ((UB[e] - LB[e])+ 1(Int)) );
/* SIZE is a token which evaluates the "size" of an array from its descriptor
*/

Tokdef Make_Desc = [base:EXP, l:EXP, u:EXP, s:EXP]EXP
		   Cons[shape_offset(Desc)]
			( .BASE:base, .LB:l, .UB:u, .STRIDE:s);
/* constructs a descriptor from its components */

Tokdef Local_array = [l:EXP, u:EXP, s:SHAPE]EXP
	EXP: Make_Desc[local_alloc( Sizeof(s) .* ((u - l)+ 1(Int))),
		  l, u, Sizeof(s)];
/* define a 1-d array of shape s */

Keep (Desc, BASE, LB, UB, STRIDE, SIZE, Make_Desc, Local_array)
