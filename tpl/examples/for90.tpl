/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


Tokdec BASE:[EXP]EXP;
Tokdec STRIDE:[EXP]EXP;
Tokdec SIZE:[EXP]EXP;
	/* Token declarations with defs in CAPSULE B */

Tokdec A1_EXP_AUX : [NAT, SHAPE,TOKEN[NAT]EXP,TOKEN[TOKEN[NAT]EXP]EXP,
		       TOKEN[NAT]EXP
		     ]EXP;
	/* Declaration of recursive token */

Tokdef A1_EXP_AUX = [	NoArrs:NAT, /* the number of arrays involved.. */
			Sh:SHAPE,  /* ...the shape of their elements */
			Arrs:TOKEN[NAT]EXP,
				/* delivers array descs [1:NoArrs] */
			Action:TOKEN[TOKEN[NAT]EXP]EXP,
				/* expansion of this is body of loop */ 
			Map:TOKEN[NAT]EXP
				/* the mapping for parameter of Action */
		     ] EXP
	EXP ?( + NoArrs(Int) - 1(Int),
	      	/* if more than one array, expand to this :*/ 
	        Var p:Ptr Sh = BASE[Arrs[NoArrs]]
			/* introduce p to access elements of 
				last array...*/
		{ A1_EXP_AUX[ 	/* scope of p is recursive expansion ...*/
			computed_nat(+ NoArrs(Int) - 1(Int)),
				/* ... with one less array ... */
			Sh,
			Arrs,
			Use [Elem:TOKEN[NAT]EXP]EXP
			   { Action[Elem];
			     p = (* p *+. STRIDE[Arrs[NoArrs]])
				/* ... adding increment to p ... */
			   },
			Use [n:NAT]EXP
			  EXP ? ( + n(Int) - + NoArrs(Int),
				  Map[n],
				  * p
				)
				/* ... and giving p as the mapping to
					be used for Elem below*/
		   ]
		},
		/* if only one array, expand to this */	
		Var q:Ptr Sh = BASE[Arrs[1]]
		Let lim = * q *+. SIZE[Arrs[1]]
			/* one element beyond the end of the 1st array*/
		Rep {
			Action[Use [n:NAT]EXP
			  EXP ? ( + n(Int) - 1(Int),
				  Map[n],
				  * q
				)
			]; /* This is where the action of the loop is
				expanded, including all the increments
			  */
			
			q = (* q *+. STRIDE[Arrs[1]]);
			*?( * q >= lim)
			/* continue loop until condition satisfied */
		}
	      );

Tokdef A1_EXP = [	NoArrs1:NAT, 
			Sh1:SHAPE,
			Arrs1:TOKEN[NAT]EXP,
			Action1:TOKEN[TOKEN[NAT]EXP]EXP
		] EXP
	/* must introduce aux token to provide mappings for parameter
		of Action */
	A1_EXP_AUX[NoArrs1, Sh1, Arrs1, Action1,
			Use [n:NAT]EXP #"This array does not exist"
		   ];

Keep (A1_EXP)
