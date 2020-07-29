/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * The main procedure defined here is evaluated which ouputs
 * assembler for data. The parameters are an evaluated exp and an index
 * into the table of externals (or 0 meaning anonymous). XXX
 */

#include <assert.h>
#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/ash.h>
#include <local/exp.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/basicread.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>
#include <construct/exp.h>

#include <flpt/flpt.h>

#include <utility/max.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include <symtab/syms.h>

#include "addr.h"
#include "out_ba.h"
#include "main.h"
#include "ibinasm.h"
#include "frames.h"
#include "procrec.h"
#include "eval.h"

extern void globalise_name(dec*);
extern procrec *procrecs;

static long G_number = 64; /* to give choice of .sdata or data */

int data_lab = 33;

/* anonymous label in data space - $$n in assember o/p */
/* but also gives it a symno for .G output */
int
next_dlab_sym(void)
{
	symnofordata(data_lab);
	return data_lab++;
}

/* various pieces of info for outputting data depending on shape */
static mm  scmm = { 127,        -128,       "\t.byte %ld :%ld\n" };
static mm uscmm = { 0xff,       0,          "\t.byte %ld :%ld\n" };
static mm  shmm = { 0x7fff,     0xffff8000, "\t.half %ld :%ld\n" };
static mm ushmm = { 0xffff,     0,          "\t.half %ld :%ld\n" };
static mm  swmm = { 0x7fffffff, 0x80000000, "\t.word %ld :%ld\n" };
static mm uswmm = { 0xffffffff, 0,          "\t.word %ld :%ld\n" };

/*
 * finds the data size from the range of an integer shape
 */
mm
maxmin(shape s)
{
	switch (s->tag) {
	case scharhd: return  scmm;
	case ucharhd: return uscmm;
	case swordhd: return  shmm;
	case uwordhd: return ushmm;
	case slonghd: return  swmm;
	case ulonghd: return uswmm;

	default:
		return uswmm;
	}

}

/*
 * Outputs the label parameter if non negative else interprets it
 * to be an index into the externals and outputs the identifier.
 */
static void
outlab(int l)
{
	if (l >= 0) {
		asm_printf( "$$%d", l);
	} else {
		char *extname = main_globals[-l - 1]->name;
		asm_printf( "%s", extname);
	}
}

/*
 * This procedure outputs all non-pack expressions and puts in label
 * values for the pack exps (putting new label numbers into their number fields)
 * which it accumulates for later application in the ptr parameter
 * of evalone. This is done to cope with the fact that the exp to evaluated
 * may contain pack operations which are graph-like.
 */
static long
evalexp(exp e)
{
	switch (e->tag) {
	case  val_tag:
	case null_tag:
	case top_tag:
		if (sh(e)->tag == offsethd && al2(sh(e)) >= 8) {
			return no(e) >> 3;
		}
		return no(e);

	case bitf_to_int_tag:
		return evalexp(son(e));

	case int_to_bitf_tag: {
		ash a;
		long  w = evalexp(son(e));
		a = ashof(sh(e));

		if (a.ashalign != 1) {
			error(ERR_INTERNAL, "should be align 1");
		}

		if (a.ashsize != 32) {
			w &= ((1 << a.ashsize) - 1);
		}

		return w;
	}

	case not_tag: return ~evalexp(son(e));
	case and_tag: return evalexp(son(e)) &  evalexp(bro(son(e)));
	case or_tag:  return evalexp(son(e)) |  evalexp(bro(son(e)));
	case xor_tag: return evalexp(son(e)) ^  evalexp(bro(son(e)));
	case shr_tag: return evalexp(son(e)) >> evalexp(bro(son(e)));
	case shl_tag: return evalexp(son(e)) << evalexp(bro(son(e)));

	case concatnof_tag: {
		ash a;
		long  wd = evalexp(son(e));
		a = ashof(sh(son(e)));
		return wd | (evalexp(bro(son(e))) << a.ashsize);
	}

	case clear_tag: {
		ash a;

		a = ashof(sh(e));
		if (a.ashsize > 32) {
			error(ERR_INTERNAL, "clearshape");
		}
		return 0;
	}

	case env_offset_tag:
	case general_env_offset_tag:
		return frame_offset(son(e));

	case env_size_tag: {
		exp tag = son(son(e));
		procrec * pr = &procrecs[no(son(tag))];
		return (pr->frame_size + pr->callee_size) >> 3;
	}

	case offset_add_tag:        return evalexp(son(e)) + evalexp(bro(son(e)));
	case offset_max_tag:        return MAX(evalexp(son(e)), evalexp(bro(son(e))));
	case offset_pad_tag:        return rounder(evalexp(son(e)), shape_align(sh(e)));
	case offset_mult_tag:       return evalexp(son(e)) * evalexp(bro(son(e)));
	case offset_div_tag:
	case offset_div_by_int_tag: return evalexp(son(e)) / evalexp(bro(son(e)));
	case offset_subtract_tag:   return evalexp(son(e)) - evalexp(bro(son(e)));
	case offset_negate_tag:     return -evalexp(son(e));

	default:
		error(ERR_INTERNAL, "tag not in evalexp");
	}

	return 0;
}

static void
set_align(int al)
{
	if (al < 16) {
		return;
	}

	if (as_file)
		asm_printop(".align%s",
		            (al == 16) ? " 1" :
		            ((al == 32) ? " 2" :
		             ((al == 64) ? " 3" : " 0")));

	out_value(0, ialign, (al == 16) ? 1 :
	          ((al == 32) ? 2 :
	           ((al == 64) ? 3 : 0)), 0);

}

static int
eval_al(shape s)
{
	if (shape_align(s) != 1) {
		return shape_align(s);
	}

	if (shape_size(s) <= 8) {
		return 8;
	}

	if (shape_size(s) <= 16) {
		return 16;
	}

	return 32;
}

static void
oneval(int val, int al, int rep)
{
	char *as = (al <= 8)
		? "\t.byte %ld :%ld\n"
		: ((al <= 16)
			? "\t.half %ld :%ld\n"
			: "\t.word %ld :%ld\n");

	set_align(al);
	if (as_file) {
		asm_printf( as, val, rep);
	}

	out_value(0, (al <= 8) ? ibyte : ((al <= 16) ? ihalf : iword), val, rep);
}

/* outputs constant expression e, rep times; */
static void
evalone(exp e, long rep)
{
	ash a;
	a = ashof(sh(e));
	switch (e->tag) {
	case string_tag: {
		long char_size = props(e);
		long  strsize = shape_size(sh(e)) / char_size;
		char *st = nostr(e);
		long  strs = shape_size(sh(e)) >> 3;
		int i, j;

		if (rep != 1 && as_file) {
			asm_printop(".repeat %ld", rep);
		}

		set_align(char_size);
		if (as_file) {
			for (j = 0; j < strsize; ) {
				switch (char_size) {
				case  8: asm_printf("\t.byte "); break;
				case 16: asm_printf("\t.half "); break;
				case 32: asm_printf("\t.word "); break;
				}

				for (i = j; i < strsize && i - j < 8; i++) {
					switch (char_size) {
					case  8: asm_printf("0x%x",             st [i]); break;
					case 16: asm_printf("0x%x",  ((short *) st)[i]); break;
					case 32: asm_printf("0x%lx", ((long  *) st)[i]); break;
					}

					if (i + 1 < strsize && i + 1 - j < 8) {
						if (assembler == ASM_GAS) {
							asm_printf(", ");
						} else {
							asm_printf(" ");
						}
					}
				}

				j = i;
				asm_printf("\n");
			}
		}

		if (rep != 1 && as_file) {
			asm_printop(".endr");
		}

		out_chars(0, iascii, strs, rep);
		out_data(st, strs);
		return;
	}

	case real_tag: {
		r2l   n;
		int i;
		n = real2longs_IEEE(&flptnos[no(e)], (a.ashsize > 32) ? 1 : 0);
		set_align(a.ashalign);
		for (i = 0; i < rep; i++) {
			switch (endian) {
			case ENDIAN_BIG:
				if (a.ashsize > 32) {
					oneval(n.i2, 32, 1);
				}
				oneval(n.i1, 32, 1);
				break;

			case ENDIAN_LITTLE:
				oneval(n.i1, 32, 1);
				if (a.ashsize > 32) {
					oneval(n.i2, 32, 1);
				}
				break;
			}
		}

		return;
	}

	case null_tag:
	case top_tag:
		no(e) = 0;

	case val_tag: {
		if (shape_size(sh(e)) > 32) {
			flt64 temp;
			int ov;
			int i;

			if (isbigval(e)) {
				temp = flt_to_f64(no(e), 0, &ov);
			} else {
				temp.big = (is_signed(sh(e)) && no(e) < 0) ? -1 : 0;
				temp.small = no(e);
			}

			for (i = 0; i < rep; i++) {
				oneval(temp.small, 32, 1);
				oneval(temp.big, 32, 1);
			}

			return;
		}

		oneval(evalexp(e), eval_al(sh(e)), rep);
		return;
	}

	case name_tag: {
		exp dc = son(e);
		dec * globdec = brog(dc); /* must be global name */
		char *name = globdec->name;
		long symdef = globdec ->sym_number;

		if (!isvar(dc) && son(dc) != NULL
		    && son(dc)->tag != proc_tag && son(dc)->tag != general_proc_tag
		    && no(e) == 0
		    && shape_size(sh(e)) == shape_size(sh(son(dc)))) {
			evalone(son(dc), rep);
			return;
		}

		set_align(32);
		if (as_file) {
			if (no(e) == 0) {
				asm_printop(".word %s : %ld", name, rep);
			} else {
				asm_printop(".word %s + %ld :%ld", name, no(e) / 8, rep);
			}
		}

		out_value(symnos[symdef], iword, no(e) / 8, rep);
		return;
	}

	case compound_tag:  {
		exp tup = son(e);
		unsigned long val;
		bool first_bits = 1;
		long bits_start = 0;
		long offs = 0;

		if (rep != 1) {
			error(ERR_INTERNAL, "CAN'T REP TUPLES");
		}
		set_align(a.ashalign);

		for (;;) {
			ash ae;
			ae = ashof(sh(bro(tup)));
			offs = no(tup);

			if (ae.ashalign == 1) {
				unsigned long vb = evalexp(bro(tup));

				if (ae.ashsize != 32) {
					vb = vb & ((1 << ae.ashsize) - 1);
				}

				if (first_bits) {
					val = 0;
					first_bits = 0;
				}

				if (offs - bits_start + ae.ashsize > 32) {
					switch (endian) {
					case ENDIAN_BIG:
						for (;;) {
							oneval(val >> 24, 8, 1);
							val <<= 8;
							bits_start += 8;
							if (offs - bits_start < 8) {
								break;
							}
						}
						break;

					case ENDIAN_LITTLE:
						for (;;) {
							oneval(val & 255, 8, 1);
							val >>= 8;
							bits_start += 8;
							if (offs - bits_start  < 8) {
								break;
							}
						}
						break;
					}
				}

				if (offs - bits_start + ae.ashsize <= 32) {
					switch (endian) {
					case ENDIAN_BIG:    val |= (vb << (32 - offs + bits_start - ae.ashsize)); break;
					case ENDIAN_LITTLE: val |= (vb << (offs - bits_start));                   break;
					}
				} else {
					error(ERR_INTERNAL, "Constant bitfield does not fit into 32 bits");
				}
			} else {
				if (!first_bits) {
					first_bits = 1;

					switch (endian) {
					case ENDIAN_BIG:
						for (;;) {
							oneval(val >> 24, 8, 1);
							val <<= 8;
							bits_start += 8;
							if (offs - bits_start <= 0) {
								break;
							}
						}
						break;

					case ENDIAN_LITTLE:
						for (;;) {
							oneval(val & 255, 8, 1);
							val >>= 8;
							bits_start += 8;
							if (offs - bits_start  <= 0) {
								break;
							}
						}
						break;
					}
				}

				while (bits_start < offs) {
					oneval(0, 0, 1);
					bits_start += 8;
				}

				evalone(bro(tup), 1);
				bits_start += shape_size(sh(bro(tup)));
			}

			if (bro(tup)->last) {
				offs += ae.ashsize;
				offs = (offs + 7) & ~7;

				for ( ; !first_bits; ) {
					switch (endian) {
					case ENDIAN_BIG:
						oneval(val >> 24, 8, 1);
						val <<= 8;
						bits_start += 8;
						if (offs - bits_start <= 0) {
							break;
						}
						break;

					case ENDIAN_LITTLE:
						assert(endian == ENDIAN_LITTLE);
						oneval(val & 255, 8, 1);
						val >>= 8;
						bits_start += 8;
						if (offs - bits_start <= 0) {
							break;
						}
						break;
					}
				}

				assert(a.ashsize >= offs);
				while (a.ashsize > offs) { /* pad out unions etc */
					oneval(0, 8, 1);
					offs += 8;
				}
				return;
			}

			tup = bro(bro(tup));
		}
	}

	case nof_tag: {
		exp s = son(e);
		if (s == NULL) {
			return;
		}

		if (rep != 1) {
			error(ERR_INTERNAL, "CAN'T REP TUPLES");
		}
		set_align(a.ashalign);

		for (;;) {
			evalone(s, 1);
			if (s->last) {
				return;
			}

			s = bro(s);
		}
	}

	case ncopies_tag: {
		if (son(e)->tag == compound_tag || son(e)->tag == concatnof_tag ||
		    son(e)->tag == nof_tag) {
			int n;
			for (n = rep * no(e); n > 0; n--) {
				evalone(son(e), 1);
			}
		} else {
			evalone(son(e), rep * no(e));
		}
		return;
	}

	case concatnof_tag: {
		if (a.ashalign == 1) {
			long  ee = evalexp(e);
			exp dad = father(e);
			ash abits;
			abits = ashof(sh(dad));
			oneval(ee, abits.ashalign, rep);
		} else {
			if (rep != 1) {
				error(ERR_INTERNAL, "CAN'T REP concat");
			}
			evalone(son(e), 1);
			evalone(bro(son(e)), 1);
		}
		return;
	}

	case clear_tag: {
		int s = eval_al(sh(e));
		if (as_file) {
			asm_printop(".space %ld", (s >> 3)* rep);
		}
		out_value(0, ispace, (s >> 3)* rep, 1);
		return;
	}

	case not_tag:
	case and_tag:
	case or_tag:
	case shl_tag:
	case shr_tag:
	case bitf_to_int_tag:
	case int_to_bitf_tag:
	case env_offset_tag:
	case general_env_offset_tag:
	case env_size_tag:
	case offset_add_tag:
	case offset_max_tag:
	case offset_pad_tag:
	case offset_mult_tag:
	case offset_div_tag:
	case offset_div_by_int_tag:
	case offset_subtract_tag:
	case offset_negate_tag: {
		long ee = evalexp(e);
		oneval(ee, eval_al(sh(e)), rep);
		return;
	}

	case seq_tag:
		if (son(son(e))->tag == prof_tag && son(son(e))->last) {
			evalone(bro(son(e)), rep);
			return;
		}

		FALL_THROUGH;

	default:
		error(ERR_INTERNAL, "tag not in evaluated");

	}
}

/*
 * This outputs data from the evaluated exp into either .sdata or .data
 * depending on size and labels this data either with either id in main_globals
 * or an anonymous label derived from l. The result is the instore "address"
 * of the constant. A negative l implies that this is the initialisation of a global
 * variable.
 */
instore
evaluated(exp e, long l, dec * dc)
{
	int lab, lab0;
	ash a;
	instore isa;
	exp z = e;

	lab = (l == 0)
		? next_dlab_sym()
		: (l < 0) ? l : -l;
	lab0 = lab;

	isa.adval    = 0;
	isa.b.offset = 0;
	isa.b.base   = lab0;

	if (e->tag == clear_tag) {
		/* uninitialised global */
		int size = (ashof(sh(e)).ashsize + 7) >> 3;
		bool temp = (l == 0 || main_globals[-lab - 1]->name[0] == '$');
		if (dc != NULL) {
			globalise_name(dc);
		}

		if (as_file) {
			asm_printf((temp) ? "\t.lcomm\t" : "\t.comm\t");
			outlab(lab);
			asm_printf( " %d\n", size);
		}

		out_value((lab >= 0) ? tempsnos[lab - 32] : symnos[-lab - 1],
		          (temp) ? ilcomm : icomm, size, 1);

		return isa;
	}

	a = ashof(sh(z));
	if (a.ashsize <= G_number) {
		if (as_file) {
			asm_printop(".sdata");
		}
		out_common(0, isdata);
	} else {
		if (as_file) {
			asm_printop(".data");
		}
		out_common(0, idata);
	}

	set_align(a.ashalign);   /* I think this is unnecessary ? bug in as */
	if (dc != NULL) {
		globalise_name(dc);
	}

	if (as_file) {
		outlab(lab);
		asm_printf(":\n");
	}

	out_common(lab > 0 ? tempsnos[lab - 32] : symnos[-lab - 1], ilabel);
	evalone(z, 1);

	return isa;
}

