/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This file contains routines for outputting constant initialisations.
 */

#include <assert.h>
#include <stdio.h>
#include <ctype.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#ifdef DWARF2
#include <local/dw2_config.h>
#endif

#include <local/szs_als.h>
#include <local/ash.h>
#include <local/fbase.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>
#include <construct/exp.h>
#include <construct/installglob.h>

#include <flpt/flpt.h>

#include <utility/max.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include "procrec.h"
#include "addrtypes.h"
#include "translate.h"
#include "inst_fmt.h"
#include "locate.h"
#include "reg.h"
#include "bitsmacs.h"
#include "eval.h"

#ifdef DWARF2
#include <dwarf2/dw2_iface.h>
#endif

/*
 * Information for outputting data
 *
 * The values are maximum, minimum, output directive.
 */
static mm  scmm = { 127,        -128,       "\t.byte\t%ld\n" };
static mm uscmm = { 0xff,       0,          "\t.byte\t%ld\n" };
static mm  shmm = { 0x7fff,     0xffff8000, "\t.half\t%ld\n" };
static mm ushmm = { 0xffff,     0,          "\t.half\t%ld\n" };
static mm  swmm = { 0x7fffffff, 0x80000000, "\t.word\t%ld\n" };
static mm uswmm = { 0xffffffff, 0,          "\t.word\t%ld\n" };

/*
 * Find the output data corresponding to a shape
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
	default:      return uswmm;
	}
}

/*
 * Find the next data label
 */
int
next_data_lab()
{
	static int data_lab = 100;
	return ++data_lab;
}

/*
 * Output a label
 */
void
outlab(int ll)
{
	/* no preference for section here */
	asm_printf("%s", ext_name(ll));
}

/*
 * Find the value of an integer constant expression
 */
static long
evalexp(exp e)
{
	switch (e->tag) {
	case val_tag:
		if (sh(e)->tag == offsethd && al2(sh(e)) >= 8) {
			return no(e) >> 3;
		} else {
			return no(e);
		}

	case general_env_offset_tag:
	case env_offset_tag: {
		exp id = son(e); /* as per tags.h, son is ident, not name */

		assert(id->tag == ident_tag);

		return boff_env_offset(id);
	}

	case env_size_tag: {
		exp tag = son(son(e));
		procrec *pr = &procrecs[no(son(tag))];
		bool leaf = (long) ((pr->needsproc.propneeds & anyproccall) == 0);
		int arg_space;

		if (leaf) {
			arg_space = 16 * 32;
		} else {
			arg_space = ((MAX(pr->needsproc.maxargs, 6 * 32) + ((16 + 1) * 32)) + 63) & ~63;
		}

		return (((pr->spacereqproc.stack + 63) & ~63) +
		         pr->needsproc.callee_size + arg_space) >> 3;
	}

	case offset_add_tag:        return evalexp(son(e)) + evalexp(bro(son(e)));
	case offset_max_tag:        return MAX(evalexp(son(e)), evalexp(bro(son(e))));
	case offset_pad_tag:        return rounder(evalexp(son(e)), shape_align(sh(e)));
	case offset_mult_tag:       return evalexp(son(e)) * evalexp(bro(son(e)));
	case offset_div_tag:
	case offset_div_by_int_tag: return evalexp(son(e)) / evalexp(bro(son(e)));
	case offset_subtract_tag:   return evalexp(son(e)) - evalexp(bro(son(e)));
	case offset_negate_tag:     return -evalexp(son(e));
	case bitf_to_int_tag:       return evalexp(son(e));

	case int_to_bitf_tag: {
		ash a;
		unsigned long w = (unsigned long) evalexp(son(e));
		a = ashof(sh(e));

		if (a.ashalign != 1 && !(sh(e)->tag == cpdhd &&
		                           a.ashalign == 32)) {
			error(ERR_SERIOUS,  "Illegal bitfield constant" );
		}

		if (a.ashsize != 32) {
			w &= ((1 << a.ashsize) - 1);
		}

		return (long) w;
	}

	case not_tag: {
		long a1 = evalexp(son(e));
		return ~a1;
	}

	case and_tag: {
		long a1 = evalexp(son(e));
		long a2 = evalexp(bro(son(e)));
		return a1 & a2;
	}

	case or_tag: {
		long a1 = evalexp(son(e));
		long a2 = evalexp(bro(son(e)));
		return a1 | a2;
	}

	case xor_tag: {
		long a1 = evalexp(son(e));
		long a2 = evalexp(bro(son(e)));
		return a1 ^ a2;
	}

	case shr_tag: {
		bool sgned = (bool) (sh(e)->tag & 1);
		long a1 = evalexp(son(e));
		long a2 = evalexp(bro(son(e)));
		if (sgned) {
			return a1 >> a2;
		} else {
			unsigned long b1 = (unsigned long) a1;
			return (long) (b1 >> a2);
		}
	}

	case shl_tag: {
		long a1 = evalexp(son(e));
		long a2 = evalexp(bro(son(e)));
		return a1 << a2;
	}

	case concatnof_tag : {
		ash s1, s2;
		unsigned long a1 = (unsigned long) evalexp(son(e));
		unsigned long a2 = (unsigned long) evalexp(bro(son(e)));

		s1 = ashof(sh(son(e)));
		s2 = ashof(sh(bro(son(e))));

		/* We should only be concatenating bitfields */
		assert(s1.ashalign == 1 && s1.ashsize <= 32);
		assert(s2.ashalign == 1 && s2.ashsize <= 32);
		assert(s1.ashsize + s2.ashsize <= 32);

		if (s2.ashsize == 32) {
			/* avoid illegal shift by 32 */
			assert(a1 == 0);
			return (long) a2;
		}
		return (long) ((a1 << s2.ashsize) | a2);
	}

	case clear_tag:
		return 0;
	}

	error(ERR_SERIOUS,  "Illegal integer constant" );
	return 0;
}

/*
 * Output a simple value
 */
static void
oneval ( int val, long al, int rep )
{
	char *as;

	if (al <= 8) {
		as = ".byte";
	} else if (al <= 16) {
		as = ".half";
	} else {
		as = ".word";
	}

	assert(rep == 1);
	asm_printop("%s %d", as, val);
}

/*
 * Output a string
 */
static void
outascii (char *s, long strsize)
{
	while (strsize > 0) {
		int i;

		asm_printf("\t.ascii\t\"");

		for (i = 0 ; strsize > 0 && i < 48 ; i++) {
			int c = (int) *s;

			switch (c) {
			case '"':  asm_printf("\\\""); break;
			case '\\': asm_printf("\\\\"); break;
			case '\t': asm_printf("\\t");  break;
			case '\n': asm_printf("\\n");  break;
			case '\r': asm_printf("\\r");  break;
			case '\f': asm_printf("\\f");  break;
			case '\b': asm_printf("\\b");  break;

			default:
				if (c >= 0 && isprint(c)) {
					asm_printf("%c", c);
				} else {
					/* octal representation */
					asm_printf("\\%.3o", (unsigned)c & 0xff);
				}
				break;
			}

			s++;
			strsize--;
		}
		asm_printf("\"\n");
	}
}

/*
 * Type representing bit patterns
 */
typedef struct {
	int bitposn;
	int value_size;
	unsigned long value;
} concbittype;

/*
 * Form an empty bit pattern
 */
static concbittype
emptyconcbit(int bitposn)
{
	concbittype start;

	start.bitposn    = bitposn;
	start.value_size = 0;
	start.value      = 0;

	return start;
}

/*
 * Output a bit pattern
 */
static void
outconcbit(concbittype c, bool ro)
{
	unsigned long w = c.value;
	int sz = c.value_size;
	int i, bytes = (sz + 7) / 8;

	if (ro) {
		insection(rodata_section);
	} else {
		insection(data_section);
	}

	if (sz == 0) {
		return;
	}

	assert(sz <= 32);

	/* output as a series of bytes */
	asm_printf("\t.byte\t");

	switch (endian) {
	case ENDIAN_LITTLE:
		for (i = 0; i < bytes; i++) {
			if (i != 0) {
				asm_printf("%c", ',');
			}

			asm_printf("%#lx", w & 0xff);
			w = w >> 8;
		}
		break;

	case ENDIAN_BIG:
		/* shift to left end of word */
		if (sz != 32) {
			w = w << (32 - sz);
		}
		for (i = 0; i < bytes; i++) {
			if (i != 0) {
				asm_printf("%c", ',');
			}

			asm_printf("%#lx", (w >> 24) & 0xff);
			w = w << 8;
		}
	}

	asm_printf("\n");
	assert ( w == 0 );
}

/*
 * Output a unary representation of the number val. val should be
 * less than or equal to 31 as it represent the number of bits
 * in a bitfield which does not occupy a whole machine word.
 */
static long
unary ( int val )
{
	int loop;
	long result = 0;

	assert (val <= 31);

	for(loop = 0; loop < val; ++loop) {
		result <<= 1;
		result |= 1;
	}

	return result;
}

/*
 * Add a value to a bit pattern
 */
static concbittype
addconcbitaux(unsigned long w, int size, concbittype b4, bool ro)
{
	int wordpos; /* bit position within word */

	if (b4.value_size == 32 ||
	     (b4.value_size != 0 && (b4.bitposn & 31) == 0)) {
		assert((b4.bitposn & 31) == 0);
		wordpos = 32;
	} else {
		wordpos = b4.bitposn & 31;
	}

	assert(size > 0);
	assert(size <= 32);
	assert(b4.value_size <= 32);
	assert(wordpos == 0 || b4.value_size <= wordpos);

	if ((size == 0 && (wordpos != 0 || b4.value_size != 0)) ||
	     (wordpos + size > 32)) {
		assert(wordpos == 32); /* should be aligned automatically */

		/* crossed boundary: output value */
		outconcbit(b4, ro);

		/* start new value */
		b4.value_size = 0;
		b4.value = 0;
		assert((b4.bitposn & 31) == 0);
	}

	if (size == 0) {
		return b4;
	}

	/* add to b4 */
	if (size == 32) {
		b4.value = w;
	} else {
		switch (endian) {
		case ENDIAN_LITTLE: b4.value = b4.value | (w << b4.value_size);        break;
		case ENDIAN_BIG:    b4.value = (b4.value << size) | (w & unary(size)); break;
		}
	}

	b4.bitposn    += size;
	b4.value_size += size;
	assert(b4.value_size <= 32);

	return b4;
}

/*
 * Evaulate a constant bit pattern
 */
static concbittype
evalconcbitaux(exp e, concbittype b4, bool ro)
{
	switch (e->tag) {
	case concatnof_tag: {
		concbittype lhs, rhs;
		lhs = evalconcbitaux(son(e), b4, ro);
		rhs = evalconcbitaux(bro(son(e)), lhs, ro);
		return rhs;
	}

	default: {
		int size = shape_size(sh(e));
		unsigned ev = (unsigned) evalexp(e);
		assert(shape_align(sh(e)) == 1);
		return addconcbitaux(ev, size, b4, ro);
	}
	}
}

/*
 * Output a constant bit pattern
 */
static void
evalconcbit(exp e, int bitposn, bool ro)
{
	concbittype start;
	start = emptyconcbit(bitposn);
	outconcbit(evalconcbitaux(e, start, ro), ro);
}

#if 1

/*
 * Does an expression represent zero?
 */
#define is_zero(e) is_comm(e)

#else

bool
is_zero(exp e)
{
	if (e == NULL) {
		return 1;
	}

	switch (e->tag) {
	case null_tag:
		return 1;

	case val_tag:
		return no(e) == 0 ? 1 : 0;

	case ncopies_tag:
	case int_to_bitf_tag:
		return is_zero(son(e));

	case compound_tag: {
		e = bro(son(e));
		for (;;) {
			if (is_zero(e) == 0) {
				return 0;
			}

			if (e->last) {
				return 1;
			}

			e = bro(bro(e));
		}

		UNREACHED;
	}

	case real_tag: {
		flt f;

		f = flptnos[no(e)];

		if (f.exp == 0) {
			int i;

			for (i = 0; i < MANT_SIZE; i++) {
				if (f.mant[i] != 0) {
					return 0;
				}
			}

			return 1; /* all zero */
		}

		return 0;
	}
	}

	return 0;
}

#endif

/*
 * Output an alignment
 */
static void
set_align(long al)
{
#if 0
	assert(al >= 8 && al <= 64);
#endif

	if (al > 8) {
		asm_printop(".align %ld", al / 8);
	}
}

/*
 * Evaulate an expression
 */
static void
evalone(exp e, int bitposn, bool ro)
{
	long al = (long) shape_align(sh(e));
	long sz = (long) shape_size(sh(e));

	if (ro) {
		insection(rodata_section);
	} else {
		insection(data_section);
	}

	set_align(al);
	if (al != 0) {
		bitposn = (int) ((bitposn / al) * al);
	}

	switch (e->tag) {
	case string_tag: {
		/* Strings or arrays of integers */
		int i, j;
		long char_size = (long) props(e);
		long strsize = sz / char_size;
		char *st = nostr(e);

		if (char_size == 8) {
			outascii(st, strsize);
			return;
		}

		if (strsize > 0) {
			set_align(char_size);
		}

		for (j = 0; j < strsize; ) {
			switch (char_size) {
			case  8: asm_printf("\t.byte\t"); break;
			case 16: asm_printf("\t.half\t"); break;
			case 32: asm_printf("\t.word\t"); break;
			}

			/* output chars in batches */
			for (i = j; i < strsize && i - j < 8; i++) {
				if (i != j) {
					asm_printf("%c", ',');
				}

				switch (char_size) {
				case  8: asm_printf("0x%x",            st [i]); break;
				case 16: asm_printf("0x%x", ((short *) st)[i]); break;
				case 32: asm_printf("0x%x", ((int   *) st)[i]); break;
				}
			}

			asm_printf("\n");
			j = i;
		}
		return;
	}

	case real_tag: {
		/* Floating point constant */
		flt *f = flptnos + no(e);
		r2l v;

		if (sz == 32) {
			v = real2longs_IEEE(f, 0);
			asm_printop(".word %d", v.i1);
		} else if (sz == 64) {
			v = real2longs_IEEE(f, 1);
			asm_printop(".word %d, %d", v.i2, v.i1);
		} else {
			v = real2longs_IEEE(f, 2);
			asm_printop(".word %d, %d, %d, %d", v.i4, v.i3, v.i2, v.i1);
		}
		return;
	}

	case null_tag:
		/* Zero */
		no(e) = 0;

		FALL_THROUGH;

	case val_tag:
		if (sh(e)->tag == s64hd || sh(e)->tag == u64hd) {
			flt64 bval;
			bval = exp_to_f64(e);
			oneval(bval.small, 32, 1);
			oneval(bval.big, 32, 1);
		}

		/* Integer constant */
		if (al2(sh(e)) >= 8 && sh(e)->tag == offsethd) {
			no(e) = no(e) >> 3;
		}
		if (al == 1) {
			evalconcbit(e, bitposn, ro);
		} else {
			oneval(no(e), al, 1);
		}
		return;

	case name_tag: {
		/* Global name */
		dec *globdec = brog(son(e));
		char *name = globdec->name;

		asm_printf("\t.word %s", name);
		if (no(e)) {
			asm_printf("+%ld",  no(e) / 8);
		}
		asm_printf("\n");
		return;
	}

	case compound_tag : {
		/* Compound values */
		exp off = son(e);
		exp tup = bro(off);
		concbittype left;
		long last_offset = 0;
		long last_align  = 0;
		long ta = (long) shape_align(sh(tup));
		long ts = shape_size(sh(tup));
		left = emptyconcbit(bitposn);

		/* output elements of aggregate recursively */
		for (;;) {
			long noff = no(off);
			long gap = noff - left.bitposn;

			/* check that component's alignment matches offset in struct */
			assert((noff / ta) * ta <= noff);
			assert(ta <= al);

			if (ts == 0) {
				if (tup->last) {
					return;
				} else {
					off = bro(bro(off));
					assert(!off->last);
					tup = bro(off);
					ta = (long) shape_align(sh(tup));
					ts = shape_size(sh(tup));
					continue;
				}
			}

			/* and is no greater that struct's alignment */
			if (noff < last_offset) {
				error(ERR_SERIOUS,  "Compound components badly ordered");
			}

			if (last_align <= 1 || ta <= 1 || gap >= ta) {
				/* get gap down */
				while (gap > 0) {
					left = addconcbitaux(0, 1, left, ro);
					gap--;
				}
			} else {
				/* alignment will handle gap */
				left.bitposn = (int) rounder(left.bitposn, ta);
			}

			last_offset = noff;
			last_align  = ta;
			assert(left.bitposn - bitposn == noff);

			if (ta == 1) {
				/* collect bitfields */
				left = evalconcbitaux(tup, left, ro);
			} else {
				/* output final bits from any previous field */
				int lb;
				outconcbit(left, ro);
				lb = left.bitposn;
				left = emptyconcbit(lb);
				evalone(tup, left.bitposn, ro);
				left.bitposn = (int) (left.bitposn + ts);
			}

			if (tup->last) {
				/* output final bits from any previous field */
				long databits = no(off) + ts;
				long trailing_bytes = (sz - databits) / 8;
				outconcbit(left, ro);
				assert(sz >= databits);

				/* pad out trailing uninitialised space, eg union */
				if (sz > databits && trailing_bytes > 0) {
					asm_printop(".skip %ld\n", trailing_bytes);
				}
				return;
			}

			off = bro(bro(off));
			assert(!off->last);
			tup = bro(off);
			ta = (long) shape_align(sh(tup));
			ts = shape_size(sh(tup));
		}

		UNREACHED;
	}

	case nof_tag: {
		/* Arrays */
		exp s = son(e);
		set_align(al);

		for (;;) {
			evalone(s, bitposn, ro);
			if (s->last) {
				return;
			}
			s = bro(s);
		}

		UNREACHED;
	}

	case ncopies_tag : {
		/* Multiple copies */
		ash c;
		int i, n = no(e);

		while (son(e)->tag == ncopies_tag) {
			e = son(e);
			n *= no(e);
		}

		e = son(e);
		c = ashof(sh(e));

		UNUSED(c);

#if 0
		if (c.ashalign != 0) {
			bitsize = (c.ashsize / c.ashalign) * c.ashalign;
		} else {
			bitsize = 0;
		}
#endif

		if (is_zero(e)) {
			set_align(al);
			asm_printop(".skip %ld", (sz + 7) >> 3);
		} else {
			for (i = 0 ; i < n ; i++) {
				evalone(e, bitposn, ro);
			}
		}

		return;
	}

	case concatnof_tag:
		/* Concatenation of arrays */
		if (al == 1) {
			/* allow for bitfields */
			evalconcbit(e, bitposn, ro);
		} else {
			ash a;
			a = ashof(sh(son(e)));
			evalone(son(e), bitposn, ro);
			bitposn = (int) (bitposn + a.ashsize);
			a = ashof(sh(bro(son(e))));
			if (a.ashalign != 0) {
				bitposn = (int) ((bitposn / a.ashalign) * a.ashalign);
			}
			evalone(bro(son(e)), bitposn, ro);
		}
		return;

	case clear_tag:
		if (al == 1) {
			/* allow for bitfields */
			evalconcbit(e, bitposn, ro);
			return;
		}

		asm_printop(".skip %ld\n", (sz + 7) >> 3);
		return;

	case not_tag:
	case and_tag:
	case or_tag:
	case shl_tag:
	case shr_tag:
	case bitf_to_int_tag:
	case int_to_bitf_tag:
	case general_env_offset_tag:
	case env_offset_tag:
	case env_size_tag:
	case offset_add_tag:
	case offset_max_tag:
	case offset_pad_tag:
	case offset_mult_tag:
	case offset_div_tag:
	case offset_div_by_int_tag:
	case offset_subtract_tag:
	case offset_negate_tag:
		asm_printop(".word %ld", evalexp(e));
		return;

	case chvar_tag:
		if (shape_size(sh(e)) == shape_size(sh(son(e)))) {
			sh(son(e)) = sh(e);
			evalone(son(e), bitposn, ro);
		} else {
			error(ERR_SERIOUS,  "Illegal chvar constant");
		}

		return;

	case minptr_tag: {
		exp p1 = son(e);
		exp p2 = bro(p1);

		if (p1->tag == name_tag && p2->tag == name_tag) {
			long n = no(p1) - no(p2);
			char *n1 = brog(son(p1))->name;
			char *n2 = brog(son(p2))->name;

			asm_printf("\t.word %s-%s", n1, n2);
			if (n < 0) {
				asm_printf("%ld", n );
			} else if ( n > 0 ) {
				asm_printf("+%ld", n);
			}
			asm_printf("\n");
			return;
		}

		FALL_THROUGH;
	}

	default:
		error(ERR_SERIOUS,  "Illegal constant" );
		return;
	}
}

bool know_size = 0;

/*
 * Output data initialisers for an expression.
 *
 * The result is the instore address of the constant. A negative
 * value of ll indicates the initialisation of a global variable.
 */
instore
evaluated(exp e, long ll, bool ro)
{
	ash a;
	int lab;
	exp z = e;
	instore isa;
	bool extnamed;
	know_size = 0;

	if (ll == 0) {
		lab = next_data_lab ();
		extnamed = 0;
	} else if (ll < 0) {
		lab = (int) ll;
		extnamed = (bool) main_globals[-lab - 1]->extnamed;
	} else { /* if (ll > 0) */
		lab = (int) (-ll);
		extnamed = (bool) main_globals[-lab - 1]->extnamed;
	}
	a = ashof(sh(e));

	isa.adval    = 0;
	isa.b.offset = 0;
	isa.b.base   = lab;

	if (is_zero(e)) {
		int byte_size = (int) ((a.ashsize + 7) >> 3);
		int align = (a.ashalign > 32 || a.ashsize > 32) ? 8 : 4;

		if (!extnamed || (e->tag == clear_tag && no(e) == -1) ||
		     /* SunOS simplifies extraction of .common from library modules */
		     (!sysV_assembler && dynamic_init_proc != NULL &&
		      !(main_globals[-lab - 1]->is_common)))
		{
			asm_printf("\t.reserve ");
			outlab(lab);
			if (sysV_assembler) {
				asm_printf(",%d,\".bss\",%d\n", byte_size, align);
			} else {
				asm_printf(",%d,\"bss\",%d\n", byte_size, align);
			}
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && (e->tag == clear_tag && no(e) == -1)) {
				note_data (lab, ro); /* do_prom */
			}
#endif
		} else {
			if (a.ashalign > 32 || a.ashsize > 32) {
				set_align(64L);
			} else {
				set_align(32L);
			}

			asm_printf("\t.common ");
			outlab(lab);
			if (sysV_assembler) {
				asm_printf(",%d,%d\n", byte_size, align);
			} else {
				asm_printf(",%d\n", byte_size);
			}
		}

		know_size = 1;
	} else {
#ifdef DWARF2
		if (diag == DIAG_DWARF2) {
			note_data (lab, ro);
		}
#endif

		if (ro) {
			insection(rodata_section);
		} else {
			insection(data_section);
		}

		if (a.ashalign > 32 || a.ashsize > 32) {
			set_align(64L);
		} else {
			set_align(32L);
		}

		outlab(lab);
		asm_printf(":\n");
		if (a.ashsize != 0) {
			evalone(z, 0, ro);
		}
		/* evalone does not output .skip to finish off */
		if (a.ashalign > 32) {
			set_align(64L);
		}
		/* return to .text for local values */
		if (ll >= 0) {
			insection(text_section);
		}
	}

	return isa;
}

