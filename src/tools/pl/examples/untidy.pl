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

String sd = "%d ";
String snl = "\n";

Proc generate = General Ptr Ptr Int(n:Int; ) Untidy
	Let x = local_alloc(Sizeof(Ptr Int) .* * n)
	Var i:Int = 0(Int)
	Rep {
		(x *+. (Sizeof(Ptr Int) .* * i)) = 
			local_alloc(Sizeof(Int) .* (* i + 1(Int)) );
		i = (* i + 1(Int));
		?(* i >= * n);
		untidy_return(x)
	};

Proc fill = top(a:Ptr Ptr Int, n:Int) 
	Var i:Int = 0 (Int)
 	Rep {
		Let ai = *(Ptr Int)(* a *+. (Sizeof(Ptr Int) .* * i))
		Var j:Int = 0(Int)
		Rep {
			(ai *+. (Sizeof(Int) .* * j)) = (* j + 1(Int));
			j = (* j + 1(Int));
			?( * j > * i);
		};
		i = (* i + 1(Int));
		?(* i >= * n);
		return(make_top)
	};

Proc print = top(a:Ptr Ptr Int, n:Int) 
	Var i:Int = 0 (Int)
 	Rep {
		Let ai = *(Ptr Int)(* a *+. (Sizeof(Ptr Int) .* * i))
		Var j:Int = 0(Int)
		Rep {
			printf[top](sd, 
			  *(Int)(ai *+. (Sizeof(Int) .* * j)));
			j = (* j + 1(Int));
			?( * j > * i);
		};
		printf[top](snl);
		i = (* i + 1(Int));
		?(* i >= * n);
		return(make_top)
	}; 
						


Proc main = top(){
	Let a = generate[Ptr Ptr Int][ 10(Int); ]Untidy
	{
		fill[top](a, 10(Int));
		print[top](a, 10(Int));
		return(make_top)
	}
};


Keep (main, generate)
