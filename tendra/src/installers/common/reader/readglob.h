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
$Log: readglob.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/08/23  13:30:59  pwe
 * no invert order, and initial ANDF-DE
 *
 * Revision 1.3  1997/02/18  12:56:07  currie
 * NEW DIAG STRUCTURE
 *
 * Revision 1.2  1995/09/15  13:28:11  currie
 * add_prefix
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/
#ifndef readglob_key
#define readglob_key 1



extern dec * capsule_tagtab;
  /* the table of tags which are available at the capsule level */

extern tok_define * capsule_toktab;
  /* the table of tokens which are available at the capsule level */

extern aldef * capsule_altab;
  /* the table of alignment tags which are available at the
     capsule level */

extern diag_tagdef * capsule_diag_tagtab;	/* OLD DIAGS */
  /* the table of diagnostic tags which are available at the
     capsule level */

extern dgtag_struct * capsule_dgtab;		/* NEW DIAGS */
  /* the table of diagnostic name tags which are available at the
     capsule level */

extern int capsule_no_of_tokens;
  /* the number of tokens at the capsule level */

extern int capsule_no_of_tags;
  /* the number of tags at the capsule level */

extern int capsule_no_of_als;
  /* the number of alignment tags at the capsule level */

extern int capsule_no_of_diagtags;	/* OLD DIAGS */
  /* the number of diagnostic tags at the capsule level */

extern int capsule_no_of_dgtags;	/* NEW DIAGS */
  /* the number of diagnostic tags at the capsule level */


extern dec * unit_tagtab;
  /* the table of tags for the current unit */

extern tok_define * unit_toktab;
  /* the table of tokens for the current unit */

extern aldef * unit_altab;
  /* the table of alignment tags for the current unit */

extern int unit_no_of_tokens;
  /* the number of tokens in the current unit */

extern int unit_no_of_tags;
  /* the number of tags in the current unit */

extern int unit_no_of_als;
  /* the number of alignment tags in the current unit */

extern dec ** unit_ind_tags;
  /* table of pointers to the tags used in the current unit */

extern tok_define ** unit_ind_tokens;
  /* table of pointers to the tokens used in the current unit */

extern aldef ** unit_ind_als;
  /* table of pointers to the alignment tags used in the current unit */


extern exp * unit_labtab;
  /* table of labels used in the current unit */

extern int unit_no_of_labels;
  /* number of labels used in the current unit */

extern int crt_tagdef_unit_no;
  /* number of current tagdef unit. -1 before tagdef units */

extern int unit_index;

extern char * make_local_name PROTO_S ((void));

extern int rep_make_proc;

extern int replace_arith_type;

extern int good_trans;

extern char *crt_filename;

extern capsule_frees * capsule_freelist;

extern int newcode;

extern char * add_prefix PROTO_S ((char *));

extern char * external_to_string PROTO_S ((external));

#ifdef NEWDIAGS
extern int within_diags;
#endif

#endif
