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


/* CAPSULE A:
 This might be the kind of capsule produced by the Fortran producer
*/

Tokdec A1_EXP: [NAT, SHAPE,TOKEN[NAT]EXP,TOKEN[TOKEN[NAT]EXP]EXP]EXP;
Tokdec Local_array: [EXP, EXP, SHAPE]EXP;
Tokdec Desc:[]SHAPE;
	/* These are token declaration which will be bound to 
		definitions which may vary from platform to platform;
		See CAPSULEs B & C
	*/
Iddec printf:proc;	

Var a:Desc;
Var b:Desc;
Var c:Desc;
/* a, b and c will correspond to pointers to Fortran arrays */

String s = "%g\n";

Proc main = top()
{
a = Local_array[1(Int), 10(Int), Double];
b = Local_array[1(Int), 10(Int), Double];
c = Local_array[1(Int), 10(Int), Double];

A1_EXP[2, Double, 
  	Use [n:NAT]EXP
	  EXP ? ( + n(Int) - 1(Int), * b, * c),
	Use [Elem:TOKEN[NAT]EXP]EXP
		{ Elem[1] = 1.0(Double);
		  Elem[2] = 2.0(Double);
		}
	];
	/* i.e set all elements of b to 2.0 and c to 1.0 */	 


A1_EXP[3, Double, 
	Use [n:NAT]EXP
	  EXP ? ( + n(Int) - 1(Int),
		  EXP ? ( + n(Int) - 2(Int),
			  EXP ? ( + n(Int) - 3(Int),
				  #"NOT A PARAMETER",
				  * b
			  ),
			  * c
		  ),
		  * a
	  ),
	Use [Elem:TOKEN[NAT]EXP]EXP 
		( Elem[1] = (*(Double)Elem[2] F+ *(Double)Elem[3]))
	];
	/* This would be the translation of the Fortran array assignment:
		a = b + c;
	*/

A1_EXP[1, Double,
	Use [n:NAT]EXP (* a),
	Use [Elem:TOKEN[NAT]EXP]EXP
		( printf[top](s, *(Double)Elem[1]) )
	];

	return(make_top)

};

Keep (main)
