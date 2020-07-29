/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef STANDARDSH_INCLUDED
#define STANDARDSH_INCLUDED

extern void select_tokdef_unit(void);
extern void add_extra_toks(void);
extern Name *tokforintsh(Bool issigned);
extern Name *tokforlongsh(Bool issigned);
extern Name *tokforshortsh(Bool issigned);
extern Name *tokforcharsh(Bool issigned);
extern Name *tokforfloatsh(void);
extern Name *tokfordoublesh(void);

#endif
