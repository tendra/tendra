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
Tokdef BV = [n:NAT]BITFIELD_VARIETY bfvar_bits(false, n);
Tokdef BF = [n:NAT]SHAPE
	bitfield(BV[n]);

Tokdef BO = [n:NAT]EXP
	shape_offset(BF[n]);

Tokdef F0 = [n:NAT]EXP
	offset_zero(alignment(BF[n]));

Tokdef I2B = [n:NAT, e:EXP]EXP change_int_to_bitfield(BV[n], e);

Var x:nof(17, BF[4]) = n_copies(17, I2B[4, 2(Int)]);

String sb = "before = %d\n";
String sa = "after  = %d\n";
Proc main = top() 
Var i:Int = 0(Int)
	Rep {
		printf[top](sb, bitfield_contents(BV[4], x,
				offset_mult(shape_offset(BF[4]), * i) ) );
		bitfield_assign(x, offset_mult(shape_offset(BF[4]), * i),
					I2B[4, 3(Int)]);
		printf[top](sa, bitfield_contents(BV[4], x,
				offset_mult(shape_offset(BF[4]), * i) ) );
		i = (* i + 1(Int));
		?( * i > 17(Int));
		return(make_top)
	};
	
					

Keep (x, main)
