/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */



#include <sym.h>
#include <exception.h>
#include <string.h>

typedef void(*init_func)();

__DO_I_TDF()
{
    int i;
    for (i = 0; i < PSIZE; i++) {
	char *x = _procedure_string_table + _procedure_table[i].irpss;
	if (strncmp("__I.TDF", x, 7) == 0) {
	    init_func f = (init_func)_procedure_table[i].adr;
	   (*f)();
	}
    }
    return;
}
