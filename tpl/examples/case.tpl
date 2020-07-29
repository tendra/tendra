/* Test for case */

Iddec printf:proc;

String s1 = "%d is not in [%d,%d]\n";
String s2 = "%d OK\n";

Proc test = top(i:Int, l:Int, u:Int)	/* report whether l<=i<=u */
        ?{  ?(* i >= * l); ?(* i <= * u);
            printf[top](s2, * i);
            return(make_top)
        |   printf[top](s1, * i, * l, * u);
            return(make_top)
        };

String s3 = "ERROR with %d\n";

Proc main = top()	/* check to see that case is working */
Var i:Int = 0(Int)
     Rep {
        Labelled {
            Case * i (0 -> l0, 1 -> l1, 2:3 -> l2, 4:10000 -> l3)
            | :l0: test[top](* i, 0(Int), 0(Int))
            | :l1: test[top](* i, 1(Int), 1(Int))
            | :l2: test[top](* i, 2(Int), 3(Int))
            | :l3: printf[top](s3, * i)
        };
    i = (* i + 1(Int));
    ?(* i > 3(Int));
    return(make_top)
 };

Keep (main, test)

