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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/

/* LOG 4 July 1994 added dwarf_types.h to unify with sparc version */
/* LOG 6/9/93 changes for sparc/ICL port of SVR4.2 djch
 * comment char is not #... introduced COMMENT_2 macros */

/* LOG 25/11/93 removed redundant expr_buf djch */

#include "config.h"
#include "common_types.h"
#include "readglob.h"
#include "table_fns.h"
#include "basicread.h"
#include "sortmacs.h"

/* machine dep headers */
#include "out.h"
#include "expmacs.h"

#include "tags.h"

#include "main_reads.h"
#include "check.h"
#include "main_reads.h"

#include "dwarf_types.h"
#include "dwarf_type.h"
#include "dwarf_out.h"
#include "diag_fns.h"
#include "dwarf_loc.h"
#include "dwarf_queue.h"
#include "dwarf_mc.h"
#include "mark_scope.h"
#include "cross_config.h"

#ifdef NEWDIAGS
#include "tags.h"
#endif

#ifndef CROSS_INCLUDE
#include <dwarf.h>
#else
#include CROSS_INCLUDE/dwarf.h>
#endif

int continue_decs;

static long lex_blk_stk_ptr = -1;

static dwarf_label lex_blk_stk[100];

#define PUSH_LEX_BLK (&lex_blk_stk[++lex_blk_stk_ptr])
#define POP_LEX_BLK  (&lex_blk_stk[lex_blk_stk_ptr--])
#define TOS_LEX_BLK  (&lex_blk_stk[lex_blk_stk_ptr])
#define CHK_LEX_STK  if (lex_blk_stk_ptr < -1) failer("lex stk underflow")

static void
out_dwarf_start_scope(dwarf_label *l)
{
	char expr_buf[100];
	
	if (lex_blk_stk_ptr == -1)
		return;
	
	sprintf(expr_buf,"%s - %s",LAB2CHAR(l->beg), LAB2CHAR(TOS_LEX_BLK->beg));
	OUT_DWARF_ATTR(AT_start_scope);
	dwarf4(expr_buf);
}

#ifdef NEWDIAGS

static void
comment_end_scope(diag_info * d)
{
	char expr_buf[100];
	sprintf(expr_buf,COMMENT_2("\t","\tEND diag_info key %d"),d->key);
	outs(expr_buf);
	outs("\n");	/* avoid 80x86 outnl which has side effect */
}

void
code_diag_info(diag_info * d, int proc_no,
			   void (*mcode)(void *), void * args)
{
	if (d == nildiag) {
		(*mcode)(args);
		return;
	}
	switch (d->key) {
    case DIAG_INFO_SCOPE: {
		next_dwarf_lab(PUSH_LEX_BLK);
		OUT_DWARF_BEG(TOS_LEX_BLK);
		cont_sib_chain(TAG_lexical_block);
		OUT_DWARF_ATTR(AT_low_pc);
		dwarf4(LAB2CHAR(TOS_LEX_BLK->beg));
		OUT_DWARF_ATTR(AT_high_pc);
		dwarf4(LAB2CHAR(TOS_LEX_BLK->end));
		leave_dwarf_blk();
		make_next_new_chain();
		code_diag_info (d->more, proc_no, mcode, args);
		OUT_DWARF_END(POP_LEX_BLK);
		CHK_LEX_STK;
		end_sib_chain();
		return;
    }
    case DIAG_INFO_SOURCE: {
		out_dwarf_sourcemark(&(d->data.source.beg));
		code_diag_info (d->more, proc_no, mcode, args);
		comment_end_scope (d);
		return;
    }
    case DIAG_INFO_ID: {
		exp x = d->data.id_scope.access;
		dwarf_label tlab;
		next_dwarf_lab(&tlab);
		OUT_DWARF_BEG(&tlab);	/* always needed for start_scope */
		while (1) {
			if (name(x) != hold_tag)
			{
				failer("access should be in hold");
				break;
			};
			x = son(x);
			if (name(x) == cont_tag && name(son(x)) == name_tag && isvar(son(son(x))))
				x = son(x);
			if ((name(x) != name_tag || isdiscarded(x))
				&& name(x) != val_tag && name(x) != null_tag)
			{
				break;	/* should do better ! */
			};
			
			if ((base_type(d->data.id_scope.typ))->key == DIAG_TYPE_INITED)
			{
				fprintf(stderr,"ERROR: %s has no diagtype... omitting\n",
						TDFSTRING2CHAR(d->data.id_scope.nme));
				break;
			}
			if (name(x) == name_tag && isglob(son(x)))
			{
				if (brog(son(x))->dec_u.dec_val.extnamed)
					break;
				else			/* static; goes out as local */
				{
					cont_sib_chain(TAG_local_variable);
					out_dwarf_start_scope(&tlab); /* only for local vars */
				}
			}
			else
				if (name(x) == name_tag && isparam(son(x)))
					cont_sib_chain(TAG_formal_parameter);
				else
				{
					cont_sib_chain(TAG_local_variable);
					out_dwarf_start_scope(&tlab);	/* only for local vars */
				};
			
			out_dwarf_name_attr(TDFSTRING2CHAR(d->data.id_scope.nme));
			out_dwarf_type_attr(d->data.id_scope.typ);
			if (!out_dwarf_loc_attr(x,proc_no))
				fprintf(stderr,"Unable to generate location info for variable '%s'\n",
						TDFSTRING2CHAR(d->data.id_scope.nme));
			leave_dwarf_blk();
			dump_type_q();
			break;
		}
		code_diag_info (d->more, proc_no, mcode, args);
		comment_end_scope (d);
		return;
    }
    case DIAG_INFO_TYPE: {
		dwarf_label tlab;
		next_dwarf_lab(&tlab);
		OUT_DWARF_BEG(&tlab);	/* always needed for start_scope */
		cont_sib_chain(TAG_typedef);
		out_dwarf_start_scope(&tlab);
		out_dwarf_name_attr(TDFSTRING2CHAR(d->data.type_scope.nme));
		out_dwarf_type_attr(d->data.type_scope.typ);
		leave_dwarf_blk();
		code_diag_info (d->more, proc_no, mcode, args);
		comment_end_scope (d);
		return;
    }
		failer("Illegal key in output_diag");
		fprintf(stderr,"key was %d\n",d->key);
		code_diag_info (d->more, proc_no, mcode, args);
	}
}

#else

void
output_diag(diag_info * d, int proc_no, exp e)
{
	if (d->key == DIAG_INFO_SOURCE)
	{
		out_dwarf_sourcemark(&(d->data.source.beg));
		return;
	}
	{
		dwarf_label tlab;
		
		mark_scope(e);
		
		if (props(e) & 0x80)
		{
			next_dwarf_lab(PUSH_LEX_BLK);
			OUT_DWARF_BEG(TOS_LEX_BLK);
			cont_sib_chain(TAG_lexical_block);
			OUT_DWARF_ATTR(AT_low_pc);
			dwarf4(LAB2CHAR(TOS_LEX_BLK->beg));
			OUT_DWARF_ATTR(AT_high_pc);
			dwarf4(LAB2CHAR(TOS_LEX_BLK->end));
			leave_dwarf_blk();
			make_next_new_chain();
		};
		
		next_dwarf_lab(&tlab);
		OUT_DWARF_BEG(&tlab);	/* always needed for start_scope */
		switch (d->key)
		{
		case DIAG_INFO_ID:
		{
			exp x = d->data.id_scope.access;
			
			if (name(x) != name_tag)
			{
				failer("diagnosing non-identifier");
				return;
			};
			
			if ((base_type(d->data.id_scope.typ))->key == DIAG_TYPE_INITED)
			{
				fprintf(stderr,"ERROR: %s %s has no diagtype... omitting\n",
						isparam(son(x)) ? "Formal parameter" : "Local variable",
						TDFSTRING2CHAR(d->data.id_scope.nme));
				break;
			}
			if (isglob(son(x)))
			{
				if (brog(son(x))->dec_u.dec_val.extnamed)
					break;
				else			/* static; goes out as local */
				{
					cont_sib_chain(TAG_local_variable);
					out_dwarf_start_scope(&tlab); /* only for local vars */
				}
			}
			else
				if (isparam(son(x)))
					cont_sib_chain(TAG_formal_parameter);
				else
				{
					cont_sib_chain(TAG_local_variable);
					out_dwarf_start_scope(&tlab);	/* only for local vars */
				};
			
			out_dwarf_name_attr(TDFSTRING2CHAR(d->data.id_scope.nme));
			out_dwarf_type_attr(d->data.id_scope.typ);
			if (!out_dwarf_loc_attr(x,proc_no))
				fprintf(stderr,"Unable to generate location info for variable '%s'\n",
						TDFSTRING2CHAR(d->data.id_scope.nme));
			leave_dwarf_blk();
			dump_type_q();
		}
		break;
		case DIAG_INFO_TYPE:
			cont_sib_chain(TAG_typedef);
			out_dwarf_start_scope(&tlab);
			out_dwarf_name_attr(TDFSTRING2CHAR(d->data.type_scope.nme));
			out_dwarf_type_attr(d->data.type_scope.typ);
			leave_dwarf_blk();
			break;
		case DIAG_INFO_TAG:
			fprintf(stderr,"diag_info_tag named %s\n",
					TDFSTRING2CHAR(d->data.tag_scope.nme));
			if (!strcmp(TDFSTRING2CHAR(d->data.tag_scope.nme),
						TDFSTRING2CHAR(d->data.tag_scope.typ->data.t_struct.nme)))
			{
				fprintf(stderr,"diag type gives name as %s\n",
						TDFSTRING2CHAR(d->data.tag_scope.typ->data.t_struct.nme));
				failer("different names in output_diag");
			}
			out_dwarf_user_type(d->data.tag_scope.typ);
			break;
		default:
			failer("Illegal key in output_diag");
			fprintf(stderr,"key was %d\n",d->key);
		}
	}
}

void
output_end_scope(diag_info * d, exp e)
{
	char expr_buf[100];
	
	sprintf(expr_buf,COMMENT_2("\t","\tEND diag_info key %d"),d->key);
	outs(expr_buf);
	outnl();
	
	if (d -> key != DIAG_INFO_SOURCE && props(e) & 0x80)
	{
		OUT_DWARF_END(POP_LEX_BLK);
		CHK_LEX_STK;
		end_sib_chain();
	}
}

#endif


