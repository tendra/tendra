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


/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/solaris/dw2_config.h,v 1.4 1998/03/15 16:00:50 pwe Exp $
--------------------------------------------------------------------------
$Log: dw2_config.h,v $
 * Revision 1.4  1998/03/15  16:00:50  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.3  1998/03/11  11:04:05  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/02/18  11:22:29  pwe
 * test corrections
 *
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.8  1998/01/09  15:00:05  pwe
 * prep restructure
 *
 * Revision 1.7  1997/12/04  19:54:49  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.6  1997/10/28  10:19:24  pwe
 * extra diags
 *
 * Revision 1.5  1997/10/23  09:33:41  pwe
 * prep extra_diags
 *
 * Revision 1.4  1997/10/10  18:33:32  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.3  1997/08/23  13:55:16  pwe
 * initial ANDF-DE
 *
 * Revision 1.2  1997/05/02  11:09:28  pwe
 * dwarf2 re return address offset
 *
 * Revision 1.1  1997/04/17  12:00:27  pwe
 * dwarf2 support
 *
--------------------------------------------------------------------------
*/

#ifndef dw2_config_key
#define dw2_config_key 1

#include "config.h"
#include "common_types.h"
#include "out.h"


#ifdef NEEDS_DEBUG_ALIGN

#define DWARF_MOD_VERSION	( DWARF_VERSION * 101 )
#define DW_CIE_MOD_VERSION	( DW_CIE_VERSION * 101 )

#else

#define DWARF_MOD_VERSION	DWARF_VERSION
#define DW_CIE_MOD_VERSION	DW_CIE_VERSION

#endif


extern long instr_count;
extern long fde_count;

#define count_ins(n)		if (instr_count >= 0) instr_count += n; \
				if (fde_count >= 0) fde_count += n
#define lost_count_ins()	instr_count = fde_count = -1
#define any_output		instr_count
#define reset_any_output	instr_count = 0


#define d_outnl() outnl()

extern void out8 PROTO_S ((void));
extern void out16 PROTO_S ((void));
extern void out32 PROTO_S ((void));
extern void dot_align PROTO_S ((long n));

extern void out_string PROTO_S ((char * s));
extern void start_string PROTO_S ((char * s));
extern void end_string PROTO_S ((void));
extern void enter_section PROTO_S ((char * s));
extern void exit_section PROTO_S ((void));
extern void outnl_comment PROTO_S ((char * s));
extern void outnl_comment_i PROTO_S ((char * s, long i));
extern void out_dwf_label PROTO_S ((long l, int set));
extern void out_code_label PROTO_S ((long l));
extern void out_dwf_dist_to_label PROTO_S ((long l));
extern void out_dwf_labdiff PROTO_S ((long lo, long hi));
extern void out_ext_label PROTO_S ((char * s));
extern void out_producer PROTO_S ((char * s));

extern int dw_is_const PROTO_S ((exp e));
extern exp dw_has_location PROTO_S ((exp e));
extern void dw2_locate_exp PROTO_S ((exp e, int locate_const, int cx));
extern void dw2_prepare_locate PROTO_S ((exp id));
extern void dw_at_procdetails PROTO_S ((void));
extern void dw2_locate_result PROTO_S ((shape sha));
extern void dw2_locate_val PROTO_S ((dg_where v));
extern void dw2_offset_exp PROTO_S ((exp e));
extern void dw2_cie PROTO_S ((void));

extern void dw2_data_aranges PROTO_S ((void));
extern void trace_dw_branch_exits PROTO_S ((exp e));

extern int dw_loc_equivalence PROTO_S ((exp a, exp b));
extern void dw_allocated PROTO_S ((dg_name nm, exp id));
extern void dw_deallocated PROTO_S ((dg_name nm));
extern void dw_all_deallocated PROTO_S ((void));


extern long dwarf_lab_num;

#define min_instr_size 4
#define framecode_factor 4
#define framedata_factor 4
#define next_dwarf_label() (++dwarf_lab_num)

#define dw_line_base -2	/* small negative for short loop end-conditions */
#define dw_line_range 16


extern void note_data PROTO_S ((int ll, bool ro));


#endif
