/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


Iddec printf:proc;

Tokdef Check = [e:EXP, u:EXP, l:EXP, lab:LABEL] EXP
	{ ?( e > u | lab); ?(e < l | lab) };


Proc main = top(p:Int)

    Var z:Int
    {
	z = div2([overflow], [overflow],
		(Let w = * p
		 { ?{ Check[w, 1000(Int), -1000(Int), L];
		      | :L: printf[top](77(Int))
		    };
		    w
		}),
		5(Int) );
	printf[top](z);
	return(make_top)
    };

Keep (main)
