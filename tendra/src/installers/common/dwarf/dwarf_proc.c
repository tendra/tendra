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



/* LOG 7/9/93 changes for SPARC SVR4.2 djch
 */
/* LOG 25/11/93 removed redundant args with UNUSED djch */

#include "config.h"
#include "common_types.h"
#include "installtypes.h"

/* machine dependant */
#include "machine.h"
#include "codermacs.h"
#include "tags.h"
#include "out.h"

#include "shapemacs.h"

/* machine dependant */
#include "expmacs.h"

#include "basicread.h"
#include "diag_config.h"
#include "dwarf_types.h"
#include "dwarf_type.h"
#include "dwarf_out.h"
#include "dwarf_mc.h"
#include "cross_config.h"

#ifndef CROSS_INCLUDE
#include <dwarf.h>
#else
#include CROSS_INCLUDE/dwarf.h>
#endif

extern int continue_decs;

void
out_dwarf_proc_args(diag_type t)
{
	if (t->key != DIAG_TYPE_PROC)
		failer("Can't output args of non proc type");
	
	if (t->data.proc.opt_args)
	{
		cont_sib_chain(TAG_unspecified_parameters);
		leave_dwarf_blk();
	}
}

void
diag_proc_begin(diag_global * d_props, int global,
				int cname, char *pname)
{
	UNUSED(cname);
	UNUSED(pname);
	
	if (!d_props)
		return;
	
	outs(COMMENT_2("\t","\tHere beginneth a proc"));
	outnl();
	if (d_props->desc->key != DIAG_ID_KEY)
		failer("proc beg without id");
	
	next_dwarf_lab(&(d_props->lab));
	OUT_DWARF_BEG(&(d_props->lab));
	
	if (global)
		cont_sib_chain(TAG_global_subroutine);
	else
		cont_sib_chain(TAG_subroutine);
	
	out_dwarf_name_attr(TDFSTRING2CHAR(d_props->desc->data.id.nme));
	out_dwarf_type_attr(d_props->desc->data.id.new_type->data.proc.result_type);
	OUT_DWARF_ATTR(AT_low_pc);
	dwarf4(LAB2CHAR(d_props->lab.beg));
	OUT_DWARF_ATTR(AT_high_pc);
	dwarf4(LAB2CHAR(d_props->lab.end));
	leave_dwarf_blk();
	make_next_new_chain();
	
	out_dwarf_sourcemark(&d_props->desc->data.id.whence); /* must be OUTSIDE blk */
	out_dwarf_proc_args(d_props->desc->data.id.new_type);
	continue_decs = 1;
}

void
diag_proc_end(diag_global * d_props)
{
	if (!d_props)
		return;
	
	outs(COMMENT_2("\t","\tHere endeth a proc"));
	outnl();
	OUT_DWARF_END(&(d_props->lab));
	end_sib_chain();
}

void
diag_val_begin(diag_global * d_props, int global,
			   int cname, char *pname)
{
	UNUSED(d_props);
	UNUSED(global);
	UNUSED(cname);
	UNUSED(pname);
	
	outs(COMMENT_2("\t","\tHere beginneth a val"));
	outnl();
}

void
diag_val_end(diag_global * d_props)
{
	UNUSED(d_props);
	
	outs(COMMENT_2("\t","\tHere endeth a val"));
	outnl();
}
