/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
