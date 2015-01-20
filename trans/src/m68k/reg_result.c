/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include <construct/installtypes.h>
#include <construct/shape.h>
#include <construct/reg_result.h>
#include <construct/exp.h>

#include <main/flags.h>

/*
 * DOES A PROCEDURE RETURN A RESULT OF A GIVEN SHAPE IN A REGISTER?
 *
 * cc has two ways of getting results from procedures.  Firstly in the
 * register D0 (or D0 and D1 in certain cases) and secondly in a section
 * of memory the address of which is passed in at the start of the
 * procedure in the A1 register and returned at the end in the D0
 * register.  This routine works out whether or not a procedure
 * delivering a result of shape sha will use the first method.
 */
bool
reg_result(shape sha)
{
	char n = name(sha);

	if (cconv == CCONV_HP) {
		/* HP cc doesn't return any tuples, unions etc in a register */
		return n != cpdhd && n != nofhd;
	} else {
		/* Return anything of size <= 32 or 64 in a register */
		long sz = shape_size(sha);
		return sz <= 32 || sz == 64;
	}
}

