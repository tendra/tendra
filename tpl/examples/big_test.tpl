/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


Iddec printf : proc;
Iddec f_var_calls : proc;
Iddec g : proc;

String results = "\nThis should print the integers 1 to %d\n\n";
String s = "%d\n";
String gs = "g:%d\n";

Var count : Int = 0(Int);


Proc f_var_calls = General Int(; i:Int ...)
Var x:Ptr Int = i
    ? { 
	? ((*(Int)(* x)) > 0(Int));
	printf [top] (s, f_var_calls [Int] [; *(Int)(* x) - 1(Int) ...; make_top]);
	f_var_calls Tail_call [*(Int)(* x) - 1(Int) ...]
      |
	count = ((* count) + 1(Int));
	return (* count)
    };







Proc main = top ()
{

    count = 0(Int);
    printf [top] (results, 4(Int));
    printf [top] (s, f_var_calls [Int] [; 2(Int) ... ; make_top]);

    return (make_top)
};

Keep (main,f_var_calls,g,s)
