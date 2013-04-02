/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <construct/exp.h>
#include <construct/shapemacs.h>

#include "expmacs.h"
#include "out.h"
#include "localflags.h"
#include "szs_als.h"

/*
 * is the result of a procedure delivering
 * this shape produced in registers.
 */
int
reg_result(shape sha)
{
	unsigned char n = name(sha);

	if (gcc_compatible) {
		int sz = shape_size(sha);

		if (n == nofhd) {
			return 0;
		}

		if (assembler == ASM_SUN) {
			if (n == cpdhd && sz > 32 && sz != 64) {
				return 0;
			}
		} else {
			if (n == cpdhd && sz != 8 && sz != 16 && sz != 32 && sz != 64) {
				return 0;
			}
		}

		return 1;
	}

	if (n == cpdhd || n == nofhd) {
		return 0;
	}

	return 1;
}

