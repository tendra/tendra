/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


Vardec y:Int;
Var x:Int = initial_value(1(Int));
Iddec printf:proc;
String s = "x = %d; y = %d\n";

Proc main = top(){
	printf[top](s, * x, * y);
	return(make_top)
};


Keep (main, x)
