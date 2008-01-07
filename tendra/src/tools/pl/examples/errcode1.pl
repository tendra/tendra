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
Tokdec TRY :[EXP, NAT, EXP]EXP;
Tokdec SET_SIGNAL_HANDLER: []EXP;
Tokdec MAKE_STACK_LIMIT:[EXP]EXP;

String sof = "OVERFLOW \n";
String sna = "NIL ACCESS\n";
String sso = "STACK OVERFLOW\n";
String send = "END\n";
String sx = "Current env = %d - %d\n";

Iddec f:proc;

Proc f = General top(;) Check_stack {
	f[top]();
	return(make_top)
};

Iddec main:proc;

Proc main = top() 
    Var i:Int
    Let p = make_null_ptr(alignment(Int))
    Let msize = env_size(main)
    Let tosize = msize .+. 
		(offset_pad(alignment(Int),shape_offset(Int)) .* 100(Int))
    Let stl = MAKE_STACK_LIMIT[tosize]

    {
	set_stack_limit(stl);
	printf[top](sx, current_env,stl);
	SET_SIGNAL_HANDLER;
	TRY[ i = * (Int) p, error_val(nil_access), printf[top](sna)];	

	printf[top](sx, current_env,
		make_stack_limit(current_env, tosize, offset_zero(alignment(Int))));

	TRY[plus([overflow], 16r7fffffff(Int), 16r1(Int)),
	    error_val(overflow),
	     printf[top](sof)
	   ];
	   
	printf[top](sx, current_env,
		make_stack_limit(current_env, tosize, offset_zero(alignment(Int))));

	
	TRY[ f[top][;], error_val(stack_overflow), printf[top](sso)];
	
	printf[top](send,i,p);
	return(make_top)  

    };


Keep (main)
