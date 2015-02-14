/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dw2_config_key
#define dw2_config_key 1

#include <reader/exp.h>
#include <local/out.h>

#include <construct/installtypes.h>

#ifdef TDF_DIAG4
#include <diag4/dg_first.h>
#include <diag4/dg_types.h>		/* TDF_DIAG4 */
#else
#include <diag3/dg_first.h>
#include <diag3/diaginfo.h>
#include <diag3/dg_types.h>		/* TDF_DIAG4 */
#endif

#define DWARF_MOD_VERSION	(needs_debug_align ? DWARF_VERSION  * 101 : DWARF_VERSION)
#define DW_CIE_MOD_VERSION	(needs_debug_align ? DW_CIE_VERSION * 101 : DW_CIE_VERSION)


extern long instr_count;
extern long fde_count;

#define count_ins(n)		if (instr_count >= 0)instr_count += n; \
				if (fde_count >= 0)fde_count += n
#define lost_count_ins()	instr_count = fde_count = -1
#define any_output		instr_count
#define reset_any_output	instr_count = 0


extern void out8(void);
extern void out16(void);
extern void out32(void);
extern void dot_align(long n);

extern void out_string(char * s);
extern void start_string(char * s);
extern void end_string(void);
extern void enter_section(char * s);
extern void exit_section(void);
extern void out_dwf_label(long l, int set);
extern void out_code_label(long l);
extern void out_dwf_dist_to_label(long l);
extern void out_dwf_labdiff(long lo, long hi);
extern void out_ext_label(char * s);
extern void out_producer(char * s);

extern int dw_is_const(exp e);
extern exp dw_has_location(exp e);
extern void dw2_locate_exp(exp e, int locate_const, int cx);
extern void dw2_prepare_locate(exp id);
extern void dw_at_procdetails(void);
extern void dw2_locate_result(shape sha);
extern void dw2_locate_val(dg_where v);
extern void dw2_offset_exp(exp e);
extern void dw2_cie(void);

extern void dw2_data_aranges(void);
extern void trace_dw_branch_exits(exp e);

extern int dw_loc_equivalence(exp a, exp b);
extern void dw_allocated(dg_name nm, exp id);
extern void dw_deallocated(dg_name nm);
extern void dw_all_deallocated(void);


extern long dwarf_lab_num;

#define min_instr_size 4
#define framecode_factor 4
#define framedata_factor 4
#define next_dwarf_label()(++dwarf_lab_num)

#define dw_line_base -2	/* small negative for short loop end-conditions */
#define dw_line_range 16


extern void note_data(int ll, bool ro);


#endif
