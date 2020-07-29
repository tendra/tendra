/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


Struct C (re:Int, im:Int);
Iddec strcmp:proc;
Iddec printf:proc;
Iddec testnl:proc;

Proc addC = C (lv:C, rv:C) 
	Let l = * lv
	Let r = * rv
	{ return(
	   Cons[shape_offset(C)] ( .re: re[l] + re[r], .im: im[l] + im[r])
	  )
	};
	
String sSTRUCT1 = "Error in STRUCT1; (%d, %d) != (4, 6)\n";
String tSTRUCT1 = "STRUCT1 OK\n";

Proc test_STRUCT1 = top()
	Let x = Cons[shape_offset(C)] (.re: 1(Int), .im:2(Int)) 
	Let y = Cons[shape_offset(C)] (.re: 3(Int), .im:4(Int))
	Let z = addC[C](x,y)
	?{	?(re[z] == 4(Int));
		?(im[z] == 6(Int));
		printf[top](tSTRUCT1);
		return(make_top)
	|
		printf[top](sSTRUCT1, re[z], im[z]);
		return(make_top)
	};

Proc test_NON_LOCALS = top()
	Var NL[visible]:Int = 12345(Int)
	{	testnl[top](current_env);
		return(make_top);
	};

String sNON_LOCALS = "Error in NON_LOCALS; %d != 12345\n";
String tNON_LOCALS = "NON_LOCALS OK \n";

Let eoNL:offset(locals_alignment,  alignment(Int))
	 = env_offset(locals_alignment, alignment(Int), NL);

Proc testnl = top(fp: pointer(locals_alignment))
	Let z = *(Int) (* fp *+. env_offset(locals_alignment,alignment(Int), NL))
	Let z1 = *(Int) (* fp *+. eoNL)
	?{	?( z == 12345(Int));
		?( z1 == 12345(Int));
		printf[top](tNON_LOCALS);
		return(make_top);
	|
		printf[top](sNON_LOCALS, z);
		return(make_top);
	};

String sGO_LOCAL_LV = 
  "Error in GO_LOCAL_LV; control should never reach here\n";
String tGO_LOCAL_LV = "GO_LOCAL_LV OK\n";

Proc test_GO_LOCAL_LV = top()
{ Labelled
	{
	  Let x = make_local_lv(l)
	  { goto_local_lv(x)
	  }
	| :l:
	  printf[top](tGO_LOCAL_LV); 
	  return(make_top)
	};
	printf[top](sGO_LOCAL_LV);
	return(make_top)
};

String sNEVER_PRINT = "This should not be printed\n";

Proc testlj = bottom(env:pointer(locals_alignment), lab:pointer(code_alignment),
			p: pointer(alignment(Int)))
{

	Var i:Int = 0(Int)
	Var j:Int = 0(Int)
	Var k: Int = 1(Int)
	Rep { i = (* i + 1(Int));
	      j = (* i * * i);
	      k = (* i + (* j + (* k + * j)));
	      ?{ ?(* k < * j); printf[top](sNEVER_PRINT)
		| make_top
		};
	      ?( * k > 0(Int))
	    };
		
	long_jump(* env, * lab)
};

String sLONG_JUMP = "Error in LONG_JUMP; control should never reach here\n";
String tLONG_JUMP = "LONG_JUMP OK\n";

Proc test_LONG_JUMP = top()
{ 
	Let x = local_alloc(Sizeof(Int) .* 100(Int))
   	Labelled
	{
	  testlj[bottom](current_env, make_local_lv(l), x)
	| :l:
	  printf[top](tLONG_JUMP); 
	  return(make_top)
	};
	printf[top](sLONG_JUMP);
	return(make_top)
};

String sN_COPIES = "Error in N_COPIES; %d != %d  at index %d\n";
String tN_COPIES = "N_COPIES OK\n";

Proc testncop = top(i:Int)
	Var x:nof(10, Int) = n_copies(10, * i)
	Var j:Int = 0(Int)
	Var noe:Int = 0(Int)
	{ Rep { Let z = 
		 *(Int)(x *+. (Sizeof(Int) .* * j))
		{
	      		?{ ?( z == * i)
	      		| printf[top](sN_COPIES, z, * i, * j);
			  noe = (* noe + 1(Int)); 
	        	  make_top;
	      		}
		};
	      j = (* j + 1(Int));
	      ?( * j < 10(Int))
	  };
	  ?{ ?(* noe == 0(Int));
	     printf[top](tN_COPIES)
	  | make_top
	  };
	  return(make_top)
	};

Proc test_N_COPIES = top()
	{ testncop[top](15(Int));
	  return(make_top)
	};

String sCONCAT_NOF = "Error in CONCAT_NOF; wrong at index %d or %d\n";
String tCONCAT_NOF = "CONCAT_NOF OK\n";

Proc testconcat = top(a:nof(4, Int), b:nof(4, Int))
	Var c: nof(8, Int) = concat_nof(* a, * b)
	Var i:Int = 0(Int)
	Let coff = Sizeof(Int) .* 4(Int)
	Var noe:Int = 0(Int)
	{ Rep 
	  { Let off =  Sizeof(Int) .* * i
	  	?{ ?( *(Int)(c *+. off) == *(Int)(a *+. off));
	     	   ?( *(Int)(c *+. (off .+. coff)) == *(Int)(b *+. off));
	  	| printf[top](sCONCAT_NOF, * i, * i);
	    	  noe = (* noe + 1(Int))
		};
	    i = (* i + 1(Int));
	    ?( * i < 4(Int))
	  };
	  ?{ ?(* noe == 0(Int));
	     printf[top](tCONCAT_NOF);
	  | make_top
	  };
	  return(make_top)
	};

Proc test_CONCAT_NOF = top()
{ testconcat[top](n_copies(4, 5(Int)), n_copies(4, 17(Int)));
  return(make_top)
};

String TS1 = "abcdef";
String SS1 = "aabcde";
String TS2 = "abcdef";
String SS2 = "bcdeff";
String sMOVE_SOME = "Error in MOVE_SOME; %s  !=  %s \n";
String tMOVE_SOME = "MOVE_SOME (%d) OK\n";

Proc test_MOVE_SOME = top()
{ move_some(overlap, TS1, TS1 *+. Sizeof(Char), Sizeof(Char) .* 5(Int));
  ?{ ?(strcmp[Int](TS1, SS1) == 0(Int));
     printf[top](tMOVE_SOME, 1(Int))
    | printf[top](sMOVE_SOME, TS1, SS1)
   }; 

  move_some(overlap, TS2 *+. Sizeof(Char), TS2, Sizeof(Char) .* 5(Int));
  ?{ ?(strcmp[Int](TS2, SS2) == 0(Int));
     printf[top](tMOVE_SOME, 2(Int))
    | printf[top](sMOVE_SOME, TS2, SS2)
   };
   return(make_top)
}; 

String sPOWER = "Error in POWER;  %d != %d\n";
String tPOWER = "POWER OK\n";



Proc testpower = top(i:Int, j:Unsigned Int, a: Int)
	Let z = power(impossible, * i, * j)
	{	?{ ?(z == * a);
	   	   printf[top](tPOWER)
		| printf[top](sPOWER, z, a)
		};
		return(make_top)
	};

Var jmem:Int;
Var imem:Unsigned Int;

String sLONG_JUMP_VAR = "Error due to incorrect allocation after LONG_JUMP\n";
Proc test_POWER = top()
	Var i:Unsigned Int = 0(Unsigned Int)
	Var j:Int = 1(Int)
	{	Rep{ testpower[top](2(Int), * i, * j);
		     j = (* j * 2(Int));
		     i = (* i + 1(Unsigned Int));
		     jmem = * j;
		     imem = * i;
		     test_LONG_JUMP[top]();
		     ?{ ?(* i == * imem); ?(* j == * jmem)
		       | printf[top](sLONG_JUMP_VAR)
		      };
		     ?( * i > 4(Unsigned Int));
		};
		return(make_top)
	};

String sMAX = "Error in MAX(%d, %d) != %d\n";
String sMIN = "Error in MIN(%d, %d) != %d\n";
String tMAXMIN = "MAX and MIN ok\n";

Proc testmaxmin = top(i:Int, j:Int)
	Let x = maximum(* i,* j)
	Let y = minimum(* i,* j)
	Var n:Int = 0(Int)
	{
	   ?{ ?( * i >= * j); 
	      ?{ ?(x != * i); 
	         printf[top](sMAX, * i, * j, x);
	         n = 1(Int)
		| make_top
               };
	       ?{ ?(y != * j); 
	          printf[top](sMIN, * i, * j, y);
	          n = 1(Int)
		|  make_top
	        } 
	       
	    | 
	      ?{ ?(x != * j); 
	         printf[top](sMAX, * i, * j, x);
	         n = 1(Int)
		| make_top
               };
	       ?{ ?(y != * i); 
	          printf[top](sMIN, * i, * j, y);
	          n = 1(Int)
		|  make_top
	        }
	    };
	    ?{ ?(* n == 0(Int));
		printf[top](tMAXMIN)
	     | make_top
	    };       

	    return(make_top)
	};

Proc test_MAXMIN = top()
	Var i:Int = 0(Int)
	Var j:Int = 10(Int)
	{ Rep { testmaxmin[top](* i, * j);
		i = (* i + 1(Int));
		j = (* j - 1(Int));
		?(* i > 20(Int));
	  };
	  return(make_top)
	};

  
Proc main = top()
{	test_STRUCT1[top]();
	test_NON_LOCALS[top]();
	test_GO_LOCAL_LV[top]();
	test_LONG_JUMP[top]();
	test_N_COPIES[top]();
	test_CONCAT_NOF[top]();
	test_MOVE_SOME[top]();
	test_POWER[top]();
	test_MAXMIN[top]();
	return(make_top)
};
	

Keep(main, test_POWER, test_LONG_JUMP)
