/* Example with structures */

Struct C (re:Double, im:Double);
	/* define TOKENs : C as a SHAPE for complex, with field offsets .re and .im
		and selectors re and im */

Iddec printf:proc;

Proc addC = C (lv:C, rv:C)	/* add two complex numbers */
        Let l = * lv
        Let r = * rv
        { return( Cons[shape_offset(C)] ( .re: re[l] F+ re[r], .im: im[l] F+ im[r]) ) } ;

String s1 = "Ans = (%g, %g)\n";

Proc main = top()
        Let x = Cons[shape_offset(C)] (.re: 1.0(Double), .im:2.0(Double))
        Let y = Cons[shape_offset(C)] (.re: 3.0(Double), .im:4.0(Double))
        Let z = addC[C](x,y)
        {   printf[top](s1, re[z], im[z]);
                /* prints out "Ans = (4, 6)" */
            return(make_top)
        };

Keep(main)

