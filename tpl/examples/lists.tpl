/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Struct L (hd:Int, tl:pointer(AL));

Al_tagdef AL = alignment(L);

Var a: nof(10, L);

Tokdef A = [ind:EXP]EXP a *+. (Sizeof(L) .* ind);

Var freel: Ptr L;

Let nil:Ptr L = make_null_ptr(AL);


Proc setup = top() 
	Var i:Int
	{
	  (A[0(Int)] *+. .tl) = nil;
	  Rep (i = 0(Int)) {
	     (A[* i + 1(Int)] *+. .tl) = A[* i];
	     i = (* i + 1(Int));
	     ?(* i >= 9(Int))
	  };
	  freel = A[9(Int)];
	  return(make_top)
	 };   

Proc cons = Ptr L (x:Int, y: Ptr L)
	Let l = * freel
	{ freel = * ( Ptr L) (l *+. .tl);
	  l = Cons[shape_offset(L)](.hd: * x, .tl: * y);
	  return(l)
	};
	
Iddec printf:proc;

String s1 = "%d ";
String s2 = "\n";
	
Proc main = top()
	Var l:Ptr L
	{ setup[top](); 
	  l = cons[Ptr L](1(Int), cons[Ptr L](2(Int), 
	                                   cons[Ptr L](3(Int), nil) ) );
	  Rep {:lab:
	   ?{ *?( * l != nil);
	      printf[top](s1, *(Int)(* l *+. .hd) );
	      l = *(Ptr L)(* l *+. .tl);
	      goto(lab)
	    | printf[top](s2); return(make_top)
	    }
	  }
	};

Keep (main)
