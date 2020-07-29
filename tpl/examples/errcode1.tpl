/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
