/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
