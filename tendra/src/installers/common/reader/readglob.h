/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef readglob_key
#define readglob_key 1

/*
 * Data used for reading and translating of TDF capsule.
 */
struct tdf_capsule {
	int				c_unitindex;		/* number of current unit */

	int				c_ntags;			/* the number of tags */
	dec				*c_tags;			/* the table of tags */

	int				c_ntokens;			/* the number of tokens */
	tok_define		*c_tokens;			/* the table of tokens */

	int				c_naltags;			/* the number of alignment tags */
	aldef			*c_altags;			/* the table of alignment tags */

	int				c_ndiagtags;		/* OLD DIAGS, the number of diagnostic tags */
	diag_tagdef		*c_diagtags;		/* OLD DIAGS, the table of diagnostic tags */

	int				c_ndgtags;			/* NEW DIAGS, the number of diagnostic tags */
	dgtag_struct	*c_dgtags;			/* NEW DIAGS, the table of diagnostic name tags */
};


struct tdf_unit {
	int				u_ntags;			/* the number of tags */
	dec				*u_tags;			/* the table of tags */
	dec				**u_ind_tags;		/* table of pointers to the tags used in this unit */

	int				u_ntokens;			/* the number of tokens */
	tok_define		*u_tokens;			/* the table of tokens */
	tok_define		**u_ind_tokens;		/* table of pointers to the tokens used in this unit */

	int				u_naltags;			/* the number of alignment tags */
	aldef			*u_altags;			/* the table of alignment tags */
	aldef			**u_ind_altags;		/* table of pointers to the alignment tags used in this unit */

	int				u_nlabels;			/* number of labels used in this unit */
	exp				*u_labels;			/* table of labels used in this unit */

	int				u_ndiagtags;
	diag_tagdef		*u_diagtags;
	diag_tagdef		**u_ind_diagtags;

	int				u_ndgtags;
	dgtag_struct	*u_dgtags;
	dgtag_struct	**u_ind_dgtags;
};

extern struct tdf_capsule cap;			/* capsule being processed */
extern struct tdf_unit *cunit;			/* unit being processed */

extern int crt_tagdef_unit_no;
/* number of current tagdef unit. -1 before tagdef units */


extern char * make_local_name(void);

extern int rep_make_proc;

extern BoolT replace_arith_type;

extern int good_trans;

extern char *crt_filename;

extern capsule_frees * capsule_freelist;

extern int newcode;

extern char * add_prefix(char *);

extern char * external_to_string(external);

#ifdef NEWDIAGS
extern int within_diags;
#endif

#endif
