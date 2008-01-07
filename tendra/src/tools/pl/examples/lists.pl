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

