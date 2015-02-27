/* $Id$ */

/*
 * Sieve of Erastothenes
 * Print out the primes less than 10000
 */

String s1 = "%d\t";	/* good strings for printf */
String s2 = "\n";

Var n: nof(10000, Char);	/* will contain1 for prime; 0 for composite */

/* Token delivering pointer to element of n */
Tokdef N = [ind:EXP]EXP n *+. (Sizeof(Char) .* ind);

Iddec printf : proc;	/* definition provided by ansi library */

Proc main = top ()
    Var i:Int
    Var j:Int
    { Rep (i = 2(Int))
        {   /* set i-th element of n to 1 */
         N[* i] = 1(Char);
         i = (* i + 1(Int));
         ?(* i >= 10000(Int))	/* NB assertion fails to continue loop */
        }
    Rep (i = 2(Int) )
        {
         ?{     ?( *(Char)N[* i] == 1(Char));
                /* if its a prime ... */
                Rep ( j = (* i + * i) )
                {	/*... wipe out composites */
                N[* j] = 0(Char);
                j = (* j + * i);
                ?(* j >= 10000(Int))
         }
         | make_top
         };
         i = (* i + 1(Int));
         ?(* i >= 100(Int))
         };
     Rep (i = 2(Int); j = 0(Int) )
        {   ?{  ?( *(Char)N[* i] == 1(Char));
                /* if it's a prime, print it */
                printf[top](s1, * i);
                 j = (* j + 1(Int));
                ?{  ?( * j == 5(Int));
                    /* print new line */
                    printf[top](s2);
                    j = 0(Int)
                 | make_top
                }
            | make_top
            };
            i = (* i + 1(Int));
            ?(* i >= 10000(Int))
         };
     return(make_top)
     };

/* main will be an external name; so will printf since it is not defined */
Keep (main)

