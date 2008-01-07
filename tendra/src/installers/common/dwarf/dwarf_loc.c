/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */



/* LOG 6/9/93 changes for sparc/ICL port of SVR4.2 djch
 *   new stuff for sparc registers  added by ra 8/9/93 */

/* LOG 27/9/93 removing the blocks aroung locations djch */
/* LOG 26/11/93 proc_no long -> int to shut up tdfc djch */

#include "config.h"
#include "common_types.h"
#include "installtypes.h"

/* machine dependent */
#include "machine.h"
#include "codermacs.h"

#include "tags.h"

/* machine dependent */
#include "out.h"

#include "shapemacs.h"

/* machine dependent */
#include "basicread.h"

#include "dwarf_types.h"
#include "dwarf_out.h"
#include "dwarf_queue.h"
#include "dwarf_type.h"

#include "dwarf_loc.h"
#include "cross_config.h"

#ifndef CROSS_INCLUDE
#include <dwarf.h>
#else
#include CROSS_INCLUDE/dwarf.h>
#endif

void
out_dwarf_const4(exp x)
{
	if (name(x) != val_tag && name(x) != null_tag)
	{
		failer("non const exp in out_dwarf_const4");
		return;
	}
	dwarf4n(no(x));
}

void
out_dwarf_const_by8(exp x)
{
	if (name(x) != val_tag)
	{
		failer("non const exp in out_dwarf_const_by8");
		return;
	}
	dwarf4n((no(x)/8));
}

void
out_dwarf_member_loc_attr(exp e)
{
	int o;
	
	OUT_DWARF_ATTR(AT_location);
	if (name(e) != val_tag)
		failer("out_mem_loc_attr");
	
#ifdef LOCS_IN_BLKS
	new_dwarf_blk2();
#else
	OUT_DWARF_LOC_BLK(6);
#endif
	o = no(e)/8;
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

#if (is80x86)
static int
ok_reg_no(int x)
{
	switch (x)
	{
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

static char
*dwarf_reg_str(int x)
{
	switch (x)
	{
	case 1:
		return ("0\t#\teax");
	case 2:
		return ("2\t#\tedx");
	case 4:
		return ("1\t#\tecx");
	case 8:
		return ("3\t#\tebx");	/* 4 is esp */
	case 0x10:
		return ("7\t#\tedi");
	case 0x20:
		return ("6\t#\tesi");
	case 0x40:
		return ("5\t#\tebp");
		/* 8 eip 9 eflags 10 fpsw 11 fpcw
		 *				 12 fpip 13 fpdp 14 st0....*/
	default:
		failer("Illegal reg no in dwarf_reg_str");
		exit(EXIT_FAILURE);
	}
}

#define DWARF_FP "5\t# ebp"

#else
#if (issparc)

static char
*dwarf_reg_str(long x)
{
    int i;
    for (i = 0 ; i < 32 ; i++) {
		if (x & 1) {
			static char buff [10];
			sprintf (buff, "%d", i);
		}
		x >>= 1;
    }
    failer ("Illegal register number in dwarf_reg_str");
    return ("???");
}

#else
error need internal to dwarf register number routines
#endif
#endif

int
out_dwarf_loc_attr(exp t, int proc_no)
{
	int rval = 1;
	
	if (name(t) != name_tag) {
		OUT_DWARF_ATTR(AT_const_value);
		out_dwarf_const4(t);
		return rval;
	}
	
#ifdef NEWDIAGS
	if (isdiscarded(t))
		return rval;	/* no location */
#endif
	
	
	OUT_DWARF_ATTR(AT_location);
#ifdef LOCS_IN_BLKS
	new_dwarf_blk2();
#endif
	{
		exp s = son(t);
		
		if (isglob(s))
		{
#ifndef LOCS_IN_BLKS
			OUT_DWARF_LOC_BLK(5);
#endif
			dwarf1(OP_ADDR);
			dwarf4(brog(s) -> dec_u.dec_val.dec_id);
		}
		else
#if (is80x86)
		{
			int p = ptno(s);
			switch (p)
			{
			case local_pl:
			{
				char expr_buf[100];
				
				sprintf(expr_buf,"%d - %sdisp%d # local var",(no(s)+no(t))/8,
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
				dwarf4n((no(s)+no(t))/8 + 8);
				dwarf1(OP_BASEREG);
				dwarf4(DWARF_FP);
				dwarf1(OP_ADD);
				break;
			case reg_pl:
				if (!ok_reg_no(no(s)))	/* fails for fp regs, so put out no atoms */
					rval = 0;
				else
				{
#ifndef LOCS_IN_BLKS
					OUT_DWARF_LOC_BLK(5);
#endif
					dwarf1(OP_REG);
					dwarf4(dwarf_reg_str(no(s)));
				}
				break;
			default:
				failer("illegal ptno in out_loc_attr");
				exit(EXIT_FAILURE);
			}
		}
#else
#if (issparc)
		{
			if (props (s) & defer_bit) {
				failer ("Deferred expression in out_loc_attr");
				rval = 0;
			} else if (props (s) & inreg_bits) {
#ifndef LOCS_IN_BLKS
				OUT_DWARF_LOC_BLK(5);
#endif
				dwarf1 (OP_REG);
				dwarf4n (no (s));
			} else if (props (s) & infreg_bits) {
				failer ("Floating register expression in out_loc_attr");
				rval = 0;
			} else {
				baseoff b;
				b = boff (s);
#ifndef LOCS_IN_BLKS
				OUT_DWARF_LOC_BLK(11);
#endif
				dwarf1 (OP_CONST);
				dwarf4n ((int) b.offset);
				dwarf1 (OP_BASEREG);
				dwarf4n ((int) b.base);
				dwarf1 (OP_ADD);
			}
		}
#else
		error need machine specific non-global location description code
#endif
#endif
			}
#ifdef LOCS_IN_BLKS
	leave_dwarf_blk2();
#endif
	return rval;
}

