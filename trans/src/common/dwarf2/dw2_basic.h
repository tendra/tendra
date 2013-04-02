/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dw2_basic_key
#define dw2_basic_key

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#include "exptypes.h"
#include <construct/installtypes.h>
#include <newdiag/dg_types.h>		/* NEW DIAGS */
#else
#include <diag/dg_first.h>
#include <diag/diaginfo.h>
#include "exptypes.h"
#include <construct/installtypes.h>
#include <diag/dg_types.h>		/* NEW DIAGS */
#endif

extern void uleb128(unsigned long value);
extern void sleb128(long value);
extern int uleb128_length(unsigned long value);
extern int sleb128_length(long value);
extern void set_attribute(int name, int form);
extern void do_compunit_header(void);
extern void close_compunit_info(void);
extern void dw_sibling_end(void);
extern void dw_at_address(long lab);
extern void dw_at_ext_lab(ext_lab lab);
extern void dw_set_ext_lab(ext_lab lab);
extern void dw_at_ext_address(dg_tag tg);
extern void set_ext_address(dg_tag tg);
extern void dw_at_abstract_lab(dg_tag tg);
extern void set_abstract_lab(dg_tag tg);
extern void dw_at_string(char* s);
extern void dw_at_form(int f);
extern void dw_at_data(int n, long d);
extern void dw_at_udata(unsigned long n);
extern void dw_at_sdata(long n);
extern void dw_at_flag(int x);
extern void dw_at_decl(short_sourcepos p);
extern void dw_no_locate(void);
extern void dw_locate_offset(int n);
extern void dw_locate_reloffset(exp e);
extern void dw_at_distance(long lo, long hi);
extern long set_dw_text_label(void);
extern void out_text_label(long n);
extern void out_loc_range(long start, long end, int inclusive);

extern long last_text_label;


#endif
