/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Produce symbol numbers for binasm (dense numbers)
 */

#include <shared/error.h>
#include <shared/xalloc.h>

#include <local/ash.h>

#include "cross_config.h"

#include <symtab/symconst.h>
#include <symtab/symtab.h>
#include <symtab/new_symbol.h>

#include <reader/basicread.h>

#include <construct/ash.h>
#include <construct/shape.h>
#include <construct/tags.h>

#include <main/flags.h>

#include <local/symtab.h>

#include "symtab.h"
#include "syms.h"
#include "main.h"

extern long currentfile;

int *symnos;
int *tempsnos;

int next_temps = 0;
int no_temps   = 0;

/*
 * Produce a symbolno for global given by ex in file filen
 */
int
symnoforext(dec * ex, int filen)
{
	exp tg = ex->dec_exp;
	shape s = ex->dec_shape;
	diag_type dt = (diag_type) 0;
	short symtype;
	short symclass;
	long v = 0;
	char *id = ex->dec_id;

	if (diag != DIAG_NONE) {
		diag_descriptor *t = ex->diag_info;
		if (t != NULL) {
			id = t->data.id.nme.ints.chars;
			dt = t->data.id.new_type;
			filen = find_file(t->data.id.whence.file->file.ints.chars);
		}
	}

	if (ex->extnamed) {
		/* it is global */
		if (name(s) == prokhd && !isvar(tg)
			&& (son(tg) == NULL || name(son(tg)) == proc_tag || name(son(tg)) == general_proc_tag)) {
			/* a declared procedure */
			if (son(tg) != NULL) {
				/* a defined procedure will be output later with this symbolno */
				return add_dense_no(0, 0);
			} else {
				symtype  = stGlobal;
				symclass = scNil;
			}
		} else {
			/* some other global */
			ash a;
			symtype  = stGlobal;
			symclass = (son(tg) != NULL)
				? ((name(son(tg))) != clear_tag ? scData : scCommon)
				: scNil;
			a = ashof(s);
			v = (a.ashsize + 7) >> 3;
		}

		return new_esym_d(id, v, symtype, symclass, dt, filen);
	} else {
		/* statics */
		if (name(s) == prokhd && !isvar(tg)
			&& (son(tg) == NULL || name(son(tg)) == proc_tag || name(son(tg)) == general_proc_tag)) {
			/* a procedure */
			symtype = stStaticProc;

			if (son(tg) != NULL) {
				return add_dense_no(0, 0);
			}

			/* a defined procedure will be output later with this symbolno */
			error(ERR_INTERNAL, "Static procs should have bodies ");
			symclass = scNil;
		} else {
			/* other statics */
			symtype  = stStatic;
			symclass = (son(tg) == NULL || name(son(tg)) != clear_tag)
				? scData : scCommon;
		}

		return new_lsym_d(id, v, symtype, symclass, dt, filen);
	}
}

/*
 * Output symbolno for start of proc
 */
int
symnoforstart(int i, int filen)
{
	dec *ex = main_globals[i];
	short symtype = (ex->extnamed) ? stProc : stStaticProc;
	char *id = ex->dec_id;
	diag_type dt = (diag_type) 0;

	if (diag != DIAG_NONE) {
		diag_descriptor *t = ex->diag_info;
		if (t != NULL) {
			id = t->data.id.nme.ints.chars;
			dt = t->data.id.new_type;
			filen = find_file(t->data.id.whence.file->file.ints.chars);
		}
	}

	return new_lsym(id, symnos[i], symtype, scText, dt, filen);
}

/*
 * Output symbolno for end of proc
 */
int
symnoforend(dec * ex, int filen)
{
	char *id = ex->dec_id;
	diag_type dt = (diag_type) 0;

	if (diag != DIAG_NONE) {
		diag_descriptor *t = ex->diag_info;
		if (t != NULL) {
			id = t->data.id.nme.ints.chars;
			dt = t->data.id.new_type;
			filen = find_file(t->data.id.whence.file->file.ints.chars);
		}
	}

	return new_lsym_d(id, 0, stEnd, scText, dt, filen);
}

/*
 * Output symbol number for data_lab and remember it in tempsnos
 */
int
symnofordata(int data_lab)
{
	int a = data_lab - 32;
	if (a >= no_temps) {
		tempsnos = xrealloc(tempsnos, (100 + a) * sizeof (int));
		no_temps = a + 100;
	}

	return tempsnos[a] = add_dense_no(currentfile, 1048575 /* ???? */ );
}

