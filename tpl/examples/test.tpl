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





