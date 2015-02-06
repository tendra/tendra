/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <construct/installtypes.h>

#ifdef TDF_DIAG4
#include <diag4/diagtypes.h>
#else
#include <diag3/diagtypes.h>
#endif

extern void dwarf4(const char *t);
extern void dwarf4n(int x);
extern void dwarf2(char *c);
extern void out_dwarf_thing(int t,char *cmt);
extern void out_dwarfone(int t,char *cmt);

extern void enter_dwarf_blk(int four,int excl, dwarf_label *lb);
extern void new_dwarf_blk2(void);
extern void new_dwarf_blk4(void);
extern void leave_dwarf_blk1(int leave);

extern void out_diagnose_prelude(void);
extern void out_diagnose_postlude(void);

extern void enter_dwarf_comp_unit(void);
extern void leave_dwarf_comp_unit(void);

extern void next_dwarf_lab(dwarf_label *p);
extern dwarf_type_label *next_dwarf_type_lab(void);
extern char *current_label_name(void);

#include <dwarf1/dw1_gbl.h>
extern void out_dwarf_name_attr(const char * const s);
#define TDFSTRING2CHAR(x)	(&(((x).ints.chars)[0]))
extern void out_dwarf_string(const char * const s);
extern void out_dwarf_sourcemark(const sourcemark * const x);

extern void out_dwarf_bytesize_attr(shape t);

#define OUT_DWARF_LOC_BLK(x)		out_dwarf_thing((int)x, "loc blk")

#define OUT_DWARF_TAG(x)		out_dwarf_thing(x, #x)
#define OUT_DWARF_TAG_NAMED(x, y)	out_dwarf_thing(x, y)
#define OUT_DWARF_ATTR(x)		out_dwarf_thing(x, #x)
#define dwarf2c(x)			out_dwarf_thing(x, #x)
#define dwarf1(x)			out_dwarfone(x, #x)

#define enter_dwarf_entry(lb)		enter_dwarf_blk(1, 0, lb)
#define leave_dwarf_blk()		leave_dwarf_blk1(1)
#define leave_dwarf_blk2()		leave_dwarf_blk1(0)
#define leave_dwarf_blk4()		leave_dwarf_blk1(1)

extern void start_sib_chain1(int d_tag, char *tag_name);
extern void cont_sib_chain1(int d_tag, char *tag_name);
extern void end_sib_chain(void);
extern void make_next_new_chain(void);

#define start_sib_chain(x)	start_sib_chain1(x, #x)
#define cont_sib_chain(x)	cont_sib_chain1(x, #x)


extern void out_dwarf_lab(H_dwarf_lab *l);
#ifdef mips
#define OUT_DWARF_BEG(x)	out_dwarf_lab((H_dwarf_lab *)&(((x)->beg)[0]))
#define OUT_DWARF_END(x)	out_dwarf_lab((H_dwarf_lab *)&(((x)->end)[0]))
#else
#define OUT_DWARF_BEG(x)	out_dwarf_lab(&((x)->beg))
#define OUT_DWARF_END(x)	out_dwarf_lab(&((x)->end))
#endif
