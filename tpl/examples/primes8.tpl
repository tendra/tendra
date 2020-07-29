/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
**  primes2.pl:
**
**    Same as primes.pl but with suitable general procedures.
*/


/* Define a recursive data structure */

Struct Chain (a:Int, b:pointer(Chain_Align));
Al_tagdef Chain_Align = alignment (Chain);

Iddec printf : proc;
Iddec falls_through_sieve : proc;
Iddec apply_sieve : proc;

Var count_down : Int;
Var next_integer : Int;
Var global_chain : pointer(Chain_Align);


String first = "The first %d primes:\n\n";
String s = "%d\n";


Proc falls_through_sieve = General Int (; z:pointer(Chain_Align) ... ) Untidy
{
    ? { *? ((* z) == make_null_ptr(Chain_Align));
	untidy_return (0(Int))
      |
	make_top
    };

    Let a_z = a [(*(Chain) (* z))]
    {
	? { ? ((a_z * a_z) > (* next_integer));
	    return (0(Int))
	  |
	    make_top
	};

	? { ? (((* next_integer) % a_z) == 0(Int));
	    untidy_return (1(Int))
	  |
	    z = b [(*(Chain) (* z))];
	    falls_through_sieve Tail_call [Same ... ]
	}
    }
};


Proc apply_sieve = General top (; z:pointer(alignment(pointer(Chain_Align))) ... ) Untidy
Var link : Chain
{
    ? { ? ((* count_down) < 1(Int));
	return (make_top)
      |
	make_top
    };

    ? { ? (falls_through_sieve [Int] [; (* global_chain) ... ] != 0(Int));
	next_integer = ((* next_integer) + 1(Int));
	apply_sieve Tail_call [Same ... ];
      |
	(link *+. .a) = (* next_integer);
	(link *+. .b) = make_null_ptr (Chain_Align);
	(* z) = link;

	printf [top] (s, (* next_integer));

	next_integer = ((* next_integer) + 1(Int));
	count_down = ((* count_down) - 1(Int));
	z = (link *+. .b);
	apply_sieve [top] [; Same ... ];	/* Cannot be a tail call */
    };
	
    untidy_return (make_top)
};


Proc sieve = top (n:Int)
{
    printf [top] (first, (* n));
    count_down = (* n);
    next_integer = 2(Int);
    global_chain = make_null_ptr (Chain_Align);
    apply_sieve Tail_call [global_chain ... ];
};


Proc main = top ()
{
    sieve [top] (25(Int));

    return (make_top)
};

Keep(main, sieve, apply_sieve, falls_through_sieve,
     first, s, global_chain, next_integer, count_down,
     Chain, Chain_Align)
