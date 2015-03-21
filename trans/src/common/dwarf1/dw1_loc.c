/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/check.h>
#include <shared/error.h>

#include <local/codermacs.h>
#include <local/out.h>

#include <reader/basicread.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/shape.h>
#include <construct/machine.h>
#include <construct/tags.h>

#include <dwarf1/dw1_consts.h>
#include <dwarf1/dw1_types.h>
#include <dwarf1/dw1_out.h>
#include <dwarf1/dw1_queue.h>
#include <dwarf1/dw1_type.h>
#include <dwarf1/dw1_loc.h>

void
out_dwarf_const4(exp x)
{
	if (name(x) != val_tag && name(x) != null_tag) {
		error(ERR_INTERNAL, "non const exp in out_dwarf_const4");
		return;
	}
	dwarf4n(no(x));
}


void
out_dwarf_const_by8(exp x)
{
	if (name(x) != val_tag) {
		error(ERR_INTERNAL, "non const exp in out_dwarf_const_by8");
		return;
	}
	dwarf4n((no(x) / 8));
}


void
out_dwarf_member_loc_attr(exp e)
{
	int o;

	OUT_DWARF_ATTR(AT_location);
	if (name(e) != val_tag) {
		error(ERR_INTERNAL, "out_mem_loc_attr");
	}

#ifdef LOCS_IN_BLKS
	new_dwarf_blk2();
#else
	OUT_DWARF_LOC_BLK(6);
#endif
	o = no(e) /8;
	dwarf1(OP_CONST);
	dwarf4n(o);
	dwarf1(OP_ADD);
#ifdef LOCS_IN_BLKS
	leave_dwarf_blk2();
#endif
}


/* given the bit offset to base of anon object */
void
out_dwarf_bit_member_loc_attr(int u)
{
	OUT_DWARF_ATTR(AT_location);

#ifdef LOCS_IN_BLKS
	new_dwarf_blk2();
#else
	OUT_DWARF_LOC_BLK(6);
#endif
	dwarf1(OP_CONST);
	dwarf4n(u/8);
	dwarf1(OP_ADD);
#ifdef LOCS_IN_BLKS
	leave_dwarf_blk2();
#endif
}


#if TRANS_X86
static int
ok_reg_no(int x)
{
	switch (x) {
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
	case 0x20:
	case 0x40:
		return 1;
	default:
		return 0;
	}
}


static char *
dwarf_reg_str(int x)
{
	switch (x) {
	case 1:
		return "0\t#\teax";
	case 2:
		return "2\t#\tedx";
	case 4:
		return "1\t#\tecx";
	case 8:
		return "3\t#\tebx";	/* 4 is esp */
	case 0x10:
		return "7\t#\tedi";
	case 0x20:
		return "6\t#\tesi";
	case 0x40:
		return "5\t#\tebp";
		/* 8 eip 9 eflags 10 fpsw 11 fpcw
		   12 fpip 13 fpdp 14 st0....*/
	default:
		error(ERR_INTERNAL, "Illegal reg no in dwarf_reg_str");
		exit(EXIT_FAILURE);
	}
}

#define DWARF_FP "5\t# ebp"

#else
#if TRANS_SPARC
static char *
dwarf_reg_str(long x)
{
	int i;
	for (i = 0; i < 32; i++) {
		if (x & 1) {
			static char buff[10];
			sprintf(buff, "%d", i);
		}
		x >>= 1;
	}
	error(ERR_INTERNAL, "Illegal register number in dwarf_reg_str");
	return "???";
}

#else
error need internal to dwarf register number routines
#endif
#endif

int
out_dwarf_loc_attr(exp t, int proc_no)
{
	int rval = 1;

	UNUSED(proc_no);

	if (name(t) != name_tag) {
		OUT_DWARF_ATTR(AT_const_value);
		out_dwarf_const4(t);
		return rval;
	}

#ifdef TDF_DIAG4
	if (isdiscarded(t)) {
		/* no location */
		return rval;
	}
#endif


	OUT_DWARF_ATTR(AT_location);
#ifdef LOCS_IN_BLKS
	new_dwarf_blk2();
#endif
	{
		exp s = son(t);

		if (isglob(s)) {
#ifndef LOCS_IN_BLKS
			OUT_DWARF_LOC_BLK(5);
#endif
			dwarf1(OP_ADDR);
			dwarf4(brog(s) -> dec_id);
		} else {
#if TRANS_X86
			int p = ptno(s);
			switch (p) {
			case local_pl: {
				char expr_buf[100];

				sprintf(expr_buf, "%d - %sdisp%d # local var", 
					(no(s) + no(t)) / 8,
					local_prefix,proc_no);
#ifndef LOCS_IN_BLKS
				OUT_DWARF_LOC_BLK(11);
#endif
				dwarf1(OP_CONST);
				dwarf4(expr_buf);
			}
				dwarf1(OP_BASEREG);
				dwarf4(DWARF_FP);
				dwarf1(OP_ADD);
				break;
			case par_pl:
#ifndef LOCS_IN_BLKS
				OUT_DWARF_LOC_BLK(11);
#endif
				dwarf1(OP_CONST);
				dwarf4n((no(s) +no(t)) /8 + 8);
				dwarf1(OP_BASEREG);
				dwarf4(DWARF_FP);
				dwarf1(OP_ADD);
				break;
			case reg_pl:
				if (!ok_reg_no(no(s))) {
					/* fails for fp regs, so put out no
					 * atoms */
					rval = 0;
				} else {
#ifndef LOCS_IN_BLKS
					OUT_DWARF_LOC_BLK(5);
#endif
					dwarf1(OP_REG);
					dwarf4(dwarf_reg_str(no(s)));
				}
				break;
			default:
				error(ERR_INTERNAL, "illegal ptno in out_loc_attr");
				exit(EXIT_FAILURE);
			}
#else
#if TRANS_SPARC
			if (props(s) & defer_bit) {
				error(ERR_INTERNAL, "Deferred expression in out_loc_attr");
				rval = 0;
			} else if (props(s) & inreg_bits) {
#ifndef LOCS_IN_BLKS
				OUT_DWARF_LOC_BLK(5);
#endif
				dwarf1(OP_REG);
				dwarf4n(no(s));
			} else if (props(s) & infreg_bits) {
				error(ERR_INTERNAL, "Floating register expression in out_loc_attr");
				rval = 0;
			} else {
				baseoff b;
				b = boff(s);
#ifndef LOCS_IN_BLKS
				OUT_DWARF_LOC_BLK(11);
#endif
				dwarf1(OP_CONST);
				dwarf4n((int)b.offset);
				dwarf1(OP_BASEREG);
				dwarf4n((int)b.base);
				dwarf1(OP_ADD);
			}
#else
		error need machine specific non-global location description code
#endif
#endif
		}
	}
#ifdef LOCS_IN_BLKS
	leave_dwarf_blk2();
#endif
	return rval;
}
