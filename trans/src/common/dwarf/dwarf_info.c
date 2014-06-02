/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <local/diag_config.h>
#include <local/out.h>
#include <local/expmacs.h>
#include <reader/exptypes.h>

#include <reader/readglob.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>
#include <reader/sortmacs.h>
#include <reader/main_reads.h>

#include <construct/tags.h>

#ifdef NEWDIAGS
#include <newdiag/diag_fns.h>
#include <newdiag/mark_scope.h>
#else
#include <diag/diag_fns.h>
#include <diag/mark_scope.h>
#include <diag/diagtypes.h>
#endif

#include <dwarf/dwarf_codes.h>
#include <dwarf/dwarf_types.h>
#include <dwarf/dwarf_type.h>
#include <dwarf/dwarf_out.h>
#include <dwarf/dwarf_loc.h>
#include <dwarf/dwarf_queue.h>
#include <dwarf/dwarf_mc.h>

#ifdef NEWDIAGS
#include <construct/tags.h>
#endif

#ifdef CROSS_INCLUDE
#include CROSS_INCLUDE/dwarf.h>
#endif

int continue_decs;

static long lex_blk_stk_ptr = -1;

static dwarf_label lex_blk_stk[100];

#define PUSH_LEX_BLK	(&lex_blk_stk[++lex_blk_stk_ptr])
#define POP_LEX_BLK	(&lex_blk_stk[lex_blk_stk_ptr--])
#define TOS_LEX_BLK	(&lex_blk_stk[lex_blk_stk_ptr])
#define CHK_LEX_STK	if (lex_blk_stk_ptr < -1) {		\
				failer("lex stk underflow");	\
			}

static void
out_dwarf_start_scope(dwarf_label *l)
{
	char expr_buf[100];

	if (lex_blk_stk_ptr == -1) {
		return;
	}

	sprintf(expr_buf, "%s - %s", LAB2CHAR(l->beg),
		LAB2CHAR(TOS_LEX_BLK->beg));
	OUT_DWARF_ATTR(AT_start_scope);
	dwarf4(expr_buf);
}


#ifdef NEWDIAGS

static void
comment_end_scope(diag_info *d)
{
	char expr_buf[100];
	sprintf(expr_buf, COMMENT_2("\t", "\tEND diag_info key %d"), d->key);
	outs(expr_buf);
	outs("\n");	/* avoid 80x86 outnl which has side effect */
}


void
code_diag_info(diag_info *d, int proc_no, void(*mcode)(void *), void *args)
{
	if (d == nildiag) {
		(*mcode)(args);
		return;
	}
	switch (d->key) {
	case DIAG_INFO_SCOPE:
		next_dwarf_lab(PUSH_LEX_BLK);
		OUT_DWARF_BEG(TOS_LEX_BLK);
		cont_sib_chain(TAG_lexical_block);
		OUT_DWARF_ATTR(AT_low_pc);
		dwarf4(LAB2CHAR(TOS_LEX_BLK->beg));
		OUT_DWARF_ATTR(AT_high_pc);
		dwarf4(LAB2CHAR(TOS_LEX_BLK->end));
		leave_dwarf_blk();
		make_next_new_chain();
		code_diag_info(d->more, proc_no, mcode, args);
		OUT_DWARF_END(POP_LEX_BLK);
		CHK_LEX_STK;
		end_sib_chain();
		return;
	case DIAG_INFO_SOURCE:
		out_dwarf_sourcemark(&(d->data.source.beg));
		code_diag_info(d->more, proc_no, mcode, args);
		comment_end_scope(d);
		return;
	case DIAG_INFO_ID: {
		exp x = d->data.id_scope.access;
		dwarf_label tlab;
		next_dwarf_lab(&tlab);
		OUT_DWARF_BEG(&tlab);	/* always needed for start_scope */
		while (1) {
			if (name(x) != hold_tag) {
				failer("access should be in hold");
				break;
			}
			x = son(x);
			if (name(x) == cont_tag && name(son(x)) == name_tag &&
			    isvar(son(son(x)))) {
				x = son(x);
			}
			if ((name(x) != name_tag || isdiscarded(x)) &&
			    name(x) != val_tag && name(x) != null_tag) {
				break;	/* should do better ! */
			}

			if ((base_type(d->data.id_scope.typ))->key ==
			    DIAG_TYPE_INITED) {
				fprintf(stderr, "ERROR: %s has no diagtype... omitting\n",
					TDFSTRING2CHAR(d->data.id_scope.nme));
				break;
			}
			if (name(x) == name_tag && isglob(son(x))) {
				if (brog(son(x)) ->dec_u.dec_val.extnamed) {
					break;
				} else {
					/* static; goes out as local */
					cont_sib_chain(TAG_local_variable);
					/* only for local vars */
					out_dwarf_start_scope(&tlab);
				}
			} else if (name(x) == name_tag && isparam(son(x))) {
				cont_sib_chain(TAG_formal_parameter);
			} else {
				cont_sib_chain(TAG_local_variable);
				/* only for local vars */
				out_dwarf_start_scope(&tlab);
			}

			out_dwarf_name_attr(TDFSTRING2CHAR(d->data.id_scope.nme));
			out_dwarf_type_attr(d->data.id_scope.typ);
			if (!out_dwarf_loc_attr(x, proc_no)) {
				fprintf(stderr, "Unable to generate location info for variable '%s'\n",
					TDFSTRING2CHAR(d->data.id_scope.nme));
			}
			leave_dwarf_blk();
			dump_type_q();
			break;
		}
		code_diag_info(d->more, proc_no, mcode, args);
		comment_end_scope(d);
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
		code_diag_info(d->more, proc_no, mcode, args);
		comment_end_scope(d);
		return;
	}
		failer("Illegal key in output_diag");
		fprintf(stderr, "key was %d\n", d->key);
		code_diag_info(d->more, proc_no, mcode, args);
	}
}

#else

void
output_diag(diag_info *d, int proc_no, exp e)
{
	if (d->key == DIAG_INFO_SOURCE) {
		out_dwarf_sourcemark(&(d->data.source.beg));
		return;
	}
	{
		dwarf_label tlab;

		mark_scope(e);

		if (props(e) & 0x80) {
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
		case DIAG_INFO_ID: {
			exp x = d->data.id_scope.access;

			if (name(x) != name_tag) {
				failer("diagnosing non-identifier");
				return;
			}

			if ((base_type(d->data.id_scope.typ))->key ==
			    DIAG_TYPE_INITED) {
				fprintf(stderr, "ERROR: %s %s has no diagtype... omitting\n",
					isparam(son(x)) ? "Formal parameter" :
					"Local variable",
					TDFSTRING2CHAR(d->data.id_scope.nme));
				break;
			}
			if (isglob(son(x))) {
				if (brog(son(x)) ->dec_u.dec_val.extnamed) {
					break;
				} else {
					/* static; goes out as local */
					cont_sib_chain(TAG_local_variable);
					/* only for local vars */
					out_dwarf_start_scope(&tlab);
				}
			} else if (isparam(son(x))) {
				cont_sib_chain(TAG_formal_parameter);
			} else {
				cont_sib_chain(TAG_local_variable);
				/* only for local vars */
				out_dwarf_start_scope(&tlab);
			}

			out_dwarf_name_attr(TDFSTRING2CHAR(d->data.id_scope.nme));
			out_dwarf_type_attr(d->data.id_scope.typ);
			if (!out_dwarf_loc_attr(x, proc_no)) {
				fprintf(stderr, "Unable to generate location info for variable '%s'\n",
					TDFSTRING2CHAR(d->data.id_scope.nme));
			}
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
			fprintf(stderr, "diag_info_tag named %s\n",
				TDFSTRING2CHAR(d->data.tag_scope.nme));
			if (!strcmp(TDFSTRING2CHAR(d->data.tag_scope.nme),
				    TDFSTRING2CHAR(d->data.tag_scope.typ->data.t_struct.nme)))
			{
				fprintf(stderr, "diag type gives name as %s\n",
					TDFSTRING2CHAR(d->data.tag_scope.typ->data.t_struct.nme));
				failer("different names in output_diag");
			}
			out_dwarf_user_type(d->data.tag_scope.typ);
			break;
		default:
			failer("Illegal key in output_diag");
			fprintf(stderr, "key was %d\n", d->key);
		}
	}
}


void
output_end_scope(diag_info *d, exp e)
{
	char expr_buf[100];

	sprintf(expr_buf, COMMENT_2("\t", "\tEND diag_info key %d"), d->key);
	outs(expr_buf);
	outnl();

	if (d->key != DIAG_INFO_SOURCE && props(e) & 0x80) {
		OUT_DWARF_END(POP_LEX_BLK);
		CHK_LEX_STK;
		end_sib_chain();
	}
}

#endif
