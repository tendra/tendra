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
$Author: pwe $
$Date: 1998/03/17 16:35:00 $
$Revision: 1.4 $
$Log: dg_aux.h,v $
 * Revision 1.4  1998/03/17  16:35:00  pwe
 * correction for non-NEWDIAGS
 *
 * Revision 1.3  1998/03/11  11:03:29  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/02/18  11:22:14  pwe
 * test corrections
 *
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/12/04  19:36:19  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.2  1997/10/23  09:21:01  pwe
 * ANDF-DE V1.7 and extra diags
 *
 * Revision 1.1  1997/08/23  13:26:40  pwe
 * initial ANDF-DE
 *
***********************************************************************/

#ifndef dg_aux_key
#define dg_aux_key

extern dg_name new_dg_name PROTO_S ((dg_name_key k));
extern dg_type new_dg_type PROTO_S ((dg_type_key k));
extern dg_info new_dg_info PROTO_S ((dg_info_key k));
extern void extend_dg_name PROTO_S ((dg_name nm));
extern void extend_dg_type PROTO_S ((dg_type nm));
extern void init_dgtag PROTO_S ((dg_tag tg));
extern dg_tag gen_tg_tag PROTO_S ((void));
extern dg_type get_qual_dg_type PROTO_S ((dg_qual_type_key qual, dg_type typ));
extern dg_type get_dg_bitfield_type PROTO_S ((dg_type typ, shape sha, bitfield_variety bv));
extern char * idname_chars PROTO_S ((dg_idname nam));
extern dg_filename get_filename PROTO_S ((long dat, char * host, char * path, char * name));
extern short_sourcepos shorten_sourcepos PROTO_S ((dg_sourcepos pos));
extern short_sourcepos end_sourcepos PROTO_S ((dg_sourcepos pos));
extern dg_type find_proc_type PROTO_S ((dg_type t));

extern exp diaginfo_exp PROTO_S ((exp e));

#ifdef NEWDIAGS

extern void diag_kill_id PROTO_S ((exp id));
extern void set_obj_ref PROTO_S ((dg_name nm));
extern exp copy_res_diag PROTO_S ((exp e, dg_info d, exp var, exp lab));
extern exp diag_hold_check PROTO_S ((exp e));
extern void start_diag_inlining PROTO_S ((exp e, dg_name dn));
extern void end_diag_inlining PROTO_S ((exp e, dg_name dn));
extern dg_info combine_diaginfo PROTO_S ((dg_info d1, dg_info d2));
extern void diag_inline_result PROTO_S ((exp e));
extern void dg_whole_comp PROTO_S ((exp whole, exp comp));
extern void dg_complete_inline PROTO_S ((exp whole, exp comp));
extern void dg_dead_code PROTO_S ((exp dead, exp prev));
extern void dg_rdnd_code PROTO_S ((exp rdnd, exp next));
extern void dg_detach_const PROTO_S ((exp part, exp whole));
extern void dg_rem_ass PROTO_S ((exp ass));
extern void dg_restruct_code PROTO_S ((exp outer, exp inner, int posn));
extern void dg_extracted PROTO_S ((exp nm, exp old));
extern void strip_dg_context PROTO_S ((exp e));
extern void make_optim_dg PROTO_S ((int reason, exp e));
extern exp copy_dg_separate PROTO_S ((exp e));

#endif

extern exp relative_exp PROTO_S ((shape s, token t));

#endif
