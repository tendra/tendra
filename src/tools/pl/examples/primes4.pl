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


Proc falls_through_sieve = General Int (y:Int, z:pointer(Chain_Align); )
{
    ? { *? ((* z) == make_null_ptr(Chain_Align));
	return (0(Int))
      |
	make_top
    };

    Let a_z = a [(*(Chain) (* z))]
    {
	? { ? ((a_z * a_z) > (* y));
	    return (0(Int))
	  |
	    make_top
	};

	? { ? (((* y) % a_z) == 0(Int));
	    return (1(Int))
	  |
	    return (falls_through_sieve [Int] [(* y), b [(*(Chain) (* z))]; ])
	}
    }
};


Proc apply_sieve = General top (z:pointer(alignment(pointer(Chain_Align))); )
Var link : Chain
{
    ? { ? ((* count_down) < 1(Int));
	return (make_top)
      |
	make_top
    };

    ? { ? (falls_through_sieve [Int] [(* next_integer), (* global_chain);] != 0(Int));
	next_integer = ((* next_integer) + 1(Int));
	apply_sieve Tail_call [Same];
      |
	(link *+. .a) = (* next_integer);
	(link *+. .b) = make_null_ptr (Chain_Align);
	(* z) = link;

	printf [top] (s, (* next_integer));

	next_integer = ((* next_integer) + 1(Int));
	count_down = ((* count_down) - 1(Int));
	apply_sieve [top] [link *+. .b; ];	/* Cannot be a tail call */
    };
	
    return (make_top)
};


Proc sieve = top (n:Int)
{
    printf [top] (first, (* n));
    count_down = (* n);
    next_integer = 2(Int);
    global_chain = make_null_ptr (Chain_Align);

    apply_sieve [top] [global_chain; ];
    return (make_top)
};


Proc main = top ()
{
    sieve [top] (25(Int));

    return (make_top)
};

Keep(main, sieve, apply_sieve, falls_through_sieve,
     first, s, global_chain, next_integer, count_down,
     Chain, Chain_Align)
