/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * tdf.c - Miscellaneous TDF routines.
 *
 * This file implements various TDF routines used by the TDF linker.
 */

#include <shared/bool.h>

#include "adt/solve-cycles.h"

#include "tdf.h"

size_t
tdf_int_size(unsigned value)
{
    size_t size = 1;

    while (value >>= 3) {
	size++;
    }
    return size;
}

void
write_usage(OStreamT *ostream,		     unsigned use)
{
    char * sep = "";

    write_char(ostream, '{');
    if (use & U_DEFD) {
	write_cstring(ostream, "DEFD");
	sep = ", ";
    }
    if (use & U_MULT) {
	write_cstring(ostream, sep);
	write_cstring(ostream, "MULT");
	sep = ", ";
    }
    if (use & U_DECD) {
	write_cstring(ostream, sep);
	write_cstring(ostream, "DECD");
	sep = ", ";
    }
    if (use & U_USED) {
	write_cstring(ostream, sep);
	write_cstring(ostream, "USED");
    }
    write_char(ostream, '}');
}
