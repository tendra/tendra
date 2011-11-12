/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: pwe $
$Date: 1998/03/15 16:00:28 $
$Revision: 1.4 $
$Log: dw2_config.h,v $
 * Revision 1.4  1998/03/15  16:00:28  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.3  1998/03/11  11:03:14  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/02/18  11:22:07  pwe
 * test corrections
 *
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.10  1998/01/09  14:47:57  pwe
 * prep restructure
 *
 * Revision 1.9  1997/12/04  20:01:33  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.8  1997/10/28  10:26:51  pwe
 * correct extra diags / locations
 *
 * Revision 1.7  1997/10/23  09:37:32  pwe
 * extra_diags
 *
 * Revision 1.6  1997/10/10  18:26:05  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.5  1997/08/23  13:46:07  pwe
 * initial ANDF-DE
 *
 * Revision 1.4  1997/04/17  11:56:09  pwe
 * dwarf2 improvements
 *
 * Revision 1.3  1997/04/02  10:33:46  pwe
 * diagnose pl_tests
 *
 * Revision 1.2  1997/03/24  11:15:50  pwe
 * dwarf2 option/default
 *
 * Revision 1.1  1997/03/20  16:24:41  pwe
 * dwarf2
 *
**********************************************************************/

#ifndef dw2_config_key
#define dw2_config_key 1

#include "config.h"

#include "dg_first.h"

#include "diaginfo.h"
#include "exptypes.h"
#include "installtypes.h"
#include "dg_types.h"		/* NEW DIAGS */

#include "exptypes.h"
#include "installtypes.h"
#include "out.h"
#include "assembler.h"
#include "localflags.h"
#include "dw2_iface.h"

#define	DWARF_MOD_VERSION	DWARF_VERSION
#define	DW_CIE_MOD_VERSION	DW_CIE_VERSION


#define d_outnl()outs("\n")

extern void out_string(char *s);
extern void start_string(char *s);
extern void end_string(void);
extern void enter_section(char *s);
extern void exit_section(void);
extern void outnl_comment(char *s);
extern void outnl_comment_i(char *s, long i);
extern void out_dwf_label(long l, int set);
extern void out_code_label(long l);
extern void out_dwf_dist_to_label(long l);
extern void out_dwf_labdiff(long lo, long hi);
extern void out_ext_label(char *s);
extern void out_producer(char *s);

extern int dw_is_const(exp e);
extern exp dw_has_location(exp e);
extern void dw2_locate_exp(exp e, int locate_const, int cx);
extern void dw2_prepare_locate(exp id);
extern void dw_at_procdetails(void);
extern void dw2_locate_result(shape sha);
extern void dw2_locate_val(dg_where v);
extern void dw2_offset_exp(exp e);
extern void dw2_data_aranges(void);

extern void dw2_cie(void);
extern void trace_dw_branch_exits(exp e);

extern int dw_loc_equivalence(exp a, exp b);
extern void dw_allocated(dg_name nm, exp id);
extern void dw_deallocated(dg_name nm);
extern void dw_all_deallocated(void);


extern long dwarf_lab_num;

#define min_instr_size		1
#define framecode_factor	1
#define framedata_factor	-4	/* registers are stored -ve from CFA */
#define next_dwarf_label()	(++dwarf_lab_num)
#define out8()			outbyte()
#define out16()			outshort()
#define out32()			outlong()

#define dw_line_base		-16	/* small negative for short loop
					   end-conditions */
#define dw_line_range		128	/* large, since we don't calculate
					   instruction lengths */


extern long instr_count;
#define any_output		instr_count
#define reset_any_output	instr_count = 0


extern void note_data(char *s);
extern void note_ro(char *s);



#endif
