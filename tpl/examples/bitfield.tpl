/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
