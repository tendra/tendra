/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CAPSULE_INCLUDED
#define CAPSULE_INCLUDED


/*
 * HIGH LEVEL DECODING ROUTINES
 *
 * This file gives the routines for decoding the highest level of TDF,
 * that of the capsule.
 */

extern int dumb_mode;
extern int show_stuff;
extern int skip_pass;
extern int show_skip;
extern int skipping;

extern string *eqn_types;
extern long no_variables;
extern string *var_types;
extern char *var_letters;
extern long *var_count;

extern binding *crt_binding;
extern long total;
extern long blank_lines;
extern void de_capsule(void);


#endif
