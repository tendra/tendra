/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: pwe $
$Date: 1998/03/15 16:00:33 $
$Revision: 1.3 $
$Log: dw2_basic.h,v $
 * Revision 1.3  1998/03/15  16:00:33  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.2  1998/03/11  11:03:38  pwe
 * DWARF optimisation info
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.8  1997/12/04  19:41:14  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.7  1997/11/06  09:22:00  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.6  1997/10/10  18:18:23  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.5  1997/08/23  13:36:34  pwe
 * initial ANDF-DE
 *
 * Revision 1.4  1997/04/17  11:50:14  pwe
 * Sparc and 80x86 support
 *
 * Revision 1.3  1997/04/01  17:19:35  pwe
 * diagnose pl_tests and locate -> platform specific
 *
 * Revision 1.2  1997/03/24  11:10:20  pwe
 * struct bitfields
 *
 * Revision 1.1  1997/03/20  16:09:02  pwe
 * first version
 *
**********************************************************************/

#ifndef dw2_basic_key
#define dw2_basic_key

#include "dg_first.h"

#include "diaginfo.h"
#include "exptypes.h"
#include "installtypes.h"
#include "dg_types.h"		/* NEW DIAGS */

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
