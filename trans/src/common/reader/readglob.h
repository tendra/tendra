/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef READGLOB_H
#define READGLOB_H

#include <construct/installtypes.h>
#include <reader/token.h>

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#include <newdiag/dg_types.h>  /* new diags */
#include <newdiag/diagtypes.h> /* old diags */
#else
#include <diag/dg_first.h>
#include <diag/diaginfo.h>
#include <diag/dg_types.h>  /* new diags */
#include <diag/diagtypes.h> /* old diags */
#endif


/* the table of tags which are available at the capsule level */
extern dec *capsule_tagtab;

/* the table of tokens which are available at the capsule level */
extern tok_define *capsule_toktab;

/* the table of alignment tags which are available at the capsule level */
extern aldef *capsule_altab;

/* the table of diagnostic tags which are available at the capsule level */
extern diag_tagdef *capsule_diag_tagtab;	/* OLD DIAGS */

/* the table of diagnostic name tags which are available at the capsule level */
extern dgtag_struct *capsule_dgtab;		/* NEW DIAGS */

/* the number of tokens at the capsule level */
extern int capsule_no_of_tokens;

/* the number of tags at the capsule level */
extern int capsule_no_of_tags;

/* the number of alignment tags at the capsule level */
extern int capsule_no_of_als;

/* the number of diagnostic tags at the capsule level */
extern int capsule_no_of_diagtags;	/* OLD DIAGS */

/* the number of diagnostic tags at the capsule level */
extern int capsule_no_of_dgtags;	/* NEW DIAGS */

/* the table of tags for the current unit */
extern dec *unit_tagtab;

/* the table of tokens for the current unit */
extern tok_define *unit_toktab;

/* the table of alignment tags for the current unit */
extern aldef *unit_altab;

/* the number of tokens in the current unit */
extern int unit_no_of_tokens;

/* the number of tags in the current unit */
extern int unit_no_of_tags;

/* the number of alignment tags in the current unit */
extern int unit_no_of_als;

/* table of pointers to the tags used in the current unit */
extern dec **unit_ind_tags;

/* table of pointers to the tokens used in the current unit */
extern tok_define **unit_ind_tokens;

/* table of pointers to the alignment tags used in the current unit */
extern aldef **unit_ind_als;

/* table of labels used in the current unit */
extern exp *unit_labtab;

/* number of labels used in the current unit */
extern int unit_no_of_labels;

/* number of current tagdef unit. -1 before tagdef units */
extern int crt_tagdef_unit_no;

extern int unit_index;

extern int rep_make_proc;

extern int replace_arith_type;

extern char *crt_filename;

extern capsule_frees *capsule_freelist;

extern int newcode;

#ifdef NEWDIAGS
extern int within_diags;
#endif

char *make_local_name(void);

char *external_to_string(external);

#endif /* READGLOB_H */
