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
$Date: 1998/01/17 15:55:46 $
$Revision: 1.1.1.1 $
$Log: diag_fns.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1998/01/09  09:30:00  pwe
 * prep restructure
 *
 * Revision 1.6  1997/11/06  09:17:53  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.5  1997/10/23  09:21:19  pwe
 * ANDF-DE V1.7 and extra diags
 *
 * Revision 1.4  1997/08/23  13:27:03  pwe
 * initial ANDF-DE
 *
 * Revision 1.3  1997/03/20  17:04:51  currie
 * Dwarf2 diags
 *
Revision 1.2  1997/02/18 12:55:51  currie
NEW DIAG STRUCTURE

 * Revision 1.1  1995/04/06  10:42:55  currie
 * Initial revision
 *
***********************************************************************/
#ifndef diag_fns_key
#define diag_fns_key 1




extern void out_diagnose_prelude PROTO_S ((void));
extern void out_diagnose_postlude PROTO_S ((void));

extern void start_make_diagdef_unit PROTO_S ((int toks, int tags, int als, int ndiags));
extern void f_make_diagdef_unit PROTO_S ((void));


extern void init_capsule_diagtags PROTO_S ((void));
extern void start_make_diagtype_unit PROTO_S ((int toks, int tags, int als, int ndiagtype));
extern linkextern f_make_diagtagextern PROTO_S ((tdfint i, external e));
extern void init_unit_diagtags PROTO_S ((int n));


#ifdef NEWDIAGS

extern exp read_exp_to_source PROTO_S ((exp body));
extern exp read_diag_id_scope PROTO_S ((exp body));
extern exp read_diag_type_scope PROTO_S ((exp body));
extern exp read_diag_tag_scope PROTO_S ((exp body));

#else

extern diag_info * read_exp_to_source PROTO_S ((void));
extern diag_info * read_diag_id_scope PROTO_S ((void));
extern diag_info * read_diag_type_scope PROTO_S ((void));
extern diag_info * read_diag_tag_scope PROTO_S ((void));

#endif


#ifndef NEWDIAGS

extern void output_diag PROTO_S ((diag_info * d, int proc_no, exp e));
extern void output_end_scope PROTO_S ((diag_info * d, exp e));

extern void diag_proc_begin PROTO_S ((diag_global * d, int global, int cname, char * pname));
extern void diag_proc_end PROTO_S ((diag_global * d));

extern void diag_val_begin PROTO_S ((diag_global * d, int global, int cname, char * pname));
extern void diag_val_end PROTO_S ((diag_global * d));

#endif


extern int unit_no_of_diagtags;
extern diag_tagdef ** unit_ind_diagtags;

extern void f_make_diagtaglink PROTO_S ((tdfint i, tdfint ext));

#ifdef NEWDIAGS
extern exp diag_locate PROTO_S ((exp e));
#endif

#endif
