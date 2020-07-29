/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef SORT_INCLUDED
#define SORT_INCLUDED


/*
 * AUXILIARY TDF SORT DECODING ROUTINES
 *
 * Each TDF sort has an associated decoding routine.  Most of the
 * routines are straightforward, and so have been automatically
 * generated directly from the TDF specification.  This module deals
 * with the few tricky cases.
 */

extern object *de_token_aux(sortname, char *);
extern void de_tdfstring_format(void);
extern void de_make_label(long);
void de_case_fn(char *, char *, char *);
void de_mk_proc_fn(char *, char *, char *, char *);
void de_solve_fn(char *, char *, char *, char *, int);
extern int warn_undeclared;

#define de_case(X)		de_case_fn(X, "bx", "ss")
#define de_labelled(X)		de_solve_fn(X, "l", "x", "x", 1)
#define de_sequence(X)		format(VERT_BRACKETS, "sequence", "+[x]")
#define de_make_proc(X)		de_mk_proc_fn(X, "S", "S?[u]t", "?[t?[u]]x")
#define de_make_string(X)	de_tdfstring_format();

#define de_make_nat(X)\
	char *num = tdf_int_str();\
	out_signed(num, 0)

#define de_make_signed_nat(X)\
	long neg = tdf_bool();\
	char *num = tdf_int_str();\
	out_signed(num,(int)neg)


#endif
