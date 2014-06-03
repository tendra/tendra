/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dw2_config_key
#define dw2_config_key 1

#ifdef NEWDIAGS

#include <newdiag/dg_first.h>
#include <reader/exptypes.h>
#include <construct/installtypes.h>
#include <newdiag/dg_types.h>		/* NEW DIAGS */

#else

#include <diag/dg_first.h>
#include <diag/diaginfo.h>
#include <reader/exptypes.h>
#include <construct/installtypes.h>
#include <diag/dg_types.h>		/* NEW DIAGS */

#endif

#include <reader/exptypes.h>
#include <construct/installtypes.h>
#include <local/out.h>
#include "assembler.h"
#include "localflags.h"
#include <dwarf2/dw2_iface.h>

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
