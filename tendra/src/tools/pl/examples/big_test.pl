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
