/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
