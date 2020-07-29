/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Iddec printf:proc;


String s = "%d\n";

String s1 = "From the array ...\n";
String s2 = "\n\nFrom the general procedure ...\n";


Var tag1_nof : nof(3, Int) = make_nof (3(Int), 2(Int), 1(Int));

Proc f3 = General Int ( a:Int ... ; )

Let p1 = *(Int) ((a *+. offset_pad (parameter_alignment (Int), shape_offset (Int))) *+.
                ( offset_pad ( alignment(Int), shape_offset(Int)) .* 0(Int)))
Let p2 = *(Int) ((a *+. offset_pad (parameter_alignment (Int), shape_offset (Int))) *+.
                ( offset_pad ( alignment(Int), shape_offset(Int)) .* 1(Int)))
Let p3 = *(Int) ((a *+. offset_pad (parameter_alignment (Int), shape_offset (Int))) *+.
                ( offset_pad ( alignment(Int), shape_offset(Int)) .* 2(Int)))

{
    printf [top] (s2);
    printf [top] (s, p1);
    printf [top] (s, p2);
    printf [top] (s, p3);

    return (0(Int))
};



Tokdef tag1_n = [n:EXP] EXP  (*(Int) (tag1_nof *+. (Sizeof(Int) .* (n - 1(Int)))));


Proc main = Int ()

Let p1 = tag1_n [1(Int)]
Let p2 = tag1_n [2(Int)]
Let p3 = tag1_n [3(Int)]
{
    printf [top] (s1);
    printf [top] (s, p1);
    printf [top] (s, p2);
    printf [top] (s, p3);

    f3 [Int] [ 0(Int), (* tag1_nof) ... ; ];

    return (0(Int))
};

Keep (main, f3)




