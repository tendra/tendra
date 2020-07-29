/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


Iddec f: proc;

Proc f = General Int(a[visible]:Int; b:Int)
	?{ ?(* b == 0(Int)); return(* a)
	   | a = (* a + 1(Int));
	     f Tail_call [ * b - 1(Int)]
	 };
	

	
Iddec printf:proc;

String s = "%d\n";
	

Proc main = top()
	Var y:Int 
	Let x =	f[Int][1(Int):a1; 2(Int); y = *(Int)a1]
	{	printf[top](s, x);
		printf[top](s, * y);
		return(make_top)
	};	
	
Keep (main,f,s)
