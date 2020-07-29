/* Example of use of high-order TOKENs */

Tokdef IF = [ boolexp:TOKEN[LABEL]EXP, thenpt:EXP, elsept:EXP] EXP
	?{ boolexp[lab]; thenpt | :lab: elsept };
	/* IF is a TOKEN which can be used to mirror a standard if ... then ... else
		construction; the boolexp is a formal TOKEN with a LABEL parameter
		which is jumped to if the boolean is false */

Iddec printf: proc;

String cs = "Correct\n";
String ws = "Wrong\n";

Proc main = top()
    Var i:Int = 0(Int)
    {
        IF[ Use [l:LABEL]EXP ?(* i == 0(Int) | l), printf[top](cs), printf[top](ws) ];
            /* in other words if (i==0) printf("Correct") else printf("Wrong") */
        IF[ Use [l:LABEL]EXP ?(* i != 0(Int) | l), printf[top](ws), printf[top](cs) ];
        i = IF[ Use [l:LABEL]EXP ?(* i != 0(Int) | l), 2(Int), 3(Int)];
        IF[ Use [l:LABEL]EXP ?(* i == 3(Int) | l), printf[top](cs), printf[top](ws) ];
        return(make_top)
     };

Keep (main)

