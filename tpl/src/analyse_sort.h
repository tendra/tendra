/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ANALYSE_SORT_INCLUDED
#define ANALYSE_SORT_INCLUDED

extern void read_tdfint(void);
extern void read_tdfbool(void);
extern void out_toksort(TokSort *);
extern void out_sort(Sort *);
extern void analyse_sort(int);
extern void expand_tok(Tokdec *, TokSort *);

#endif
