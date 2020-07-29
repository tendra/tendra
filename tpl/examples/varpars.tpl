/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


Iddec printf:proc;

Iddec printnl:proc;

Proc f = General Int(n[visible]:Int; a:Int ...)
	Var x:Ptr Int = a
	Var sum[visible]:Int = 0(Int)
	?{ ?(* n == 0(Int)); return (0(Int))
	 | Rep {
	 	printnl[top](current_env);
	 	sum = (* sum + *(Int)(* x));
	 	x = (* x *+. offset_pad(parameter_alignment(Int),
	 			shape_offset(Int)) );
	 	n = (* n - 1(Int));
	 	?( * n <= 0(Int));
	   };
	   return (* sum)
	 };
	 
Let o_sum: offset(locals_alignment, alignment(Int)) 
		= env_offset(locals_alignment, alignment(Int), sum);
Let o_n:offset(callers_alignment(true),alignment(Int))
	 	= env_offset(callers_alignment(true), alignment(Int), n);  
	    
String s = "%d\n";
String s1 = "%d   %d\n";

Proc printnl = top(fp:pointer((locals_alignment, callers_alignment(true),
		callees_alignment(true))) ) {
	printf[top](s1, *(Int)(* fp *+. o_sum), *(Int)(* fp *+. o_n) );
	return(make_top)
	};	

Proc g = General Int(n1:Int; a:Int ...)
	{  return(f[Int][* n1; Same ... ]) };
	
Proc h = General Int( ; a:Int,  b:Int) 
	{ return (f[Int][2(Int); Same ...]) };	    


Proc main = top() {
	printf[top](s, g[Int][5(Int); 1(Int),2(Int),3(Int),4(Int),5(Int)
					...]);
	printf[top](s, h[Int][; 7(Int), 8(Int)]);
	return (make_top)
};

Keep (main,f,o_sum,o_n,printnl,g,h)
