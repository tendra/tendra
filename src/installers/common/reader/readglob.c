/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:45 $
$Revision: 1.1.1.1 $
$Log: readglob.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/08/23  13:30:56  pwe
 * no invert order, and initial ANDF-DE
 *
 * Revision 1.2  1997/02/18  12:56:06  currie
 * NEW DIAG STRUCTURE
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/
#include "config.h"
#include "common_types.h"



#include "readglob.h"

/* VARIABLES */
/* All variables except good_trans are initialised. This assumes
that translation stops after the first error */

dec * capsule_tagtab;
  /* the table of tags which are available at the capsule level */

tok_define * capsule_toktab;
  /* the table of tokens which are available at the capsule level */

aldef * capsule_altab;
  /* the table of alignment tags which are available at the
     capsule level */

diag_tagdef * capsule_diag_tagtab;	/* OLD DIAGS */
  /* the table of diagnostic tags which are available at the
     capsule level */

dgtag_struct * capsule_dgtab;		/* NEW DIAGS */
  /* the table of diagnostic tags which are available at the
     capsule level */

int capsule_no_of_tokens;
  /* the number of tokens at the capsule level */

int capsule_no_of_tags;
  /* the number of tags at the capsule level */

int capsule_no_of_als;
  /* the number of alignment tags at the capsule level */

int capsule_no_of_diagtags;	/* OLD DIAGS */
  /* the number of diagnostic tags at the capsule level */

int capsule_no_of_dgtags;	/* NEW DIAGS */
  /* the number of diagnostic tags at the capsule level */


dec * unit_tagtab;
  /* the table of tags for the current unit */

tok_define * unit_toktab;
  /* the table of tokens for the current unit */

aldef * unit_altab;
  /* the table of alignment tags for the current unit */

int unit_no_of_tokens;
  /* the number of tokens in the current unit */

int unit_no_of_tags;
  /* the number of tags in the current unit */

int unit_no_of_als;
  /* the number of alignment tags in the current unit */

dec ** unit_ind_tags;
  /* table of pointers to the tags used in the current unit */

tok_define ** unit_ind_tokens;
  /* table of pointers to the tokens used in the current unit */

aldef ** unit_ind_als;
  /* table of pointers to the alignment tags used in the current unit */


exp * unit_labtab;
  /* table of labels used in the current unit */

int unit_no_of_labels;
  /* number of labels used in the current unit */

int crt_tagdef_unit_no;
  /* number of current tagdef unit. -1 before tagdef units */

int unit_index;
  /* number of current unit */

int rep_make_proc = 1;  /* identify any make_procs not in make_id_tagdef*/

int replace_arith_type = 0;	/* do not use C definitions of promote
				   etc. */

int good_trans = 0;		/* 0 if translation is good, 1 for error
				*/

char *crt_filename;

capsule_frees * capsule_freelist = (capsule_frees*)0;

int newcode = 1;

#ifdef NEWDIAGS
int within_diags = 0;	/* mark name_tag if it's not used for producing code */
#endif
