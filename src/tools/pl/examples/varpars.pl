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
