/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/check.h>
#include <shared/error.h>

#include <local/fbase.h>


#if FS_NO_ANSI_ENVIRON
#include <floatingpoint.h>
#else
#include <float.h>
#endif

#include <reader/basicread.h>

#include <construct/shape.h>
#include <construct/flpt.h>
#include <construct/tags.h>
#include <construct/f64.h>

#include <main/flags.h>

#include "assembler.h"
#include "instrs.h"
#include "evaluate.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "codex.h"
#include "translate.h"
#include "utility.h"
#include "xdb_basics.h"
#include "68k_globals.h"
#include "localexpmacs.h"

extern int is_comm(exp);
extern char *get_pointer_name(void *);
extern double atof(const char *);
extern double frexp(double, int *);


#define  par_pl		1	/* On the stack (procedure argument) */
#define  var_pl		2	/* On the stack (allocated variable) */

#ifndef tdf3
#define  par2_pl        4       /* Caller arguments accessed by use of A5 */
#define  par3_pl        5       /* Caller arguments accessed by use of SP */
#endif

int convert_floats = 1;

/*
    NAME OF THE CONSTANT BEING EVALUATED
*/

static char *ext_eval_name = "???";


/*
    All external constants created are formed into a bro-list.
*/

exp const_list = NULL;


/*
    In outputting data constants, current_op is the list of values currently
    being built up.  These values are all of size current_sz.  Values not
    yet of this size are built up in pvalue, which contains psz bits.
*/

static mach_op *current_op = NULL;
static long current_sz = 0;


/*
    An instruction corresponding to current_op is output, and current_op
    is reset.
*/

static void eval_instr
(void)
{
    if (current_op) {
	int s = ins(current_sz, m_as_byte, m_as_short, m_as_long);
	make_instr(s, current_op, NULL, 0);
	current_op = NULL;
    }
    current_sz = 0;
    return;
}


/*
    The operand op of size sz is added to current_op.
*/

void eval_op
(long sz, mach_op *op)
{
    static mach_op *last_op;
    if (sz != current_sz) {
	eval_instr();
	current_op = op;
	current_sz = sz;
    } else {
	last_op->of = op;
    }
    last_op = op;
    return;
}

/*
    The expression e, is evaluated and the integer result is returned.
    (from trans386)
*/
extern int PIC_code;

long  evalexp
(exp e)
{
   switch (name(e)) {
   case  val_tag:
   case null_tag:
   case top_tag:
    {
       int k = no(e);
       if (is_offset(e))k /= 8;
       return k;
    }
   case bitf_to_int_tag:
    {
       return evalexp(son(e));
    }
   case int_to_bitf_tag:
    {
       long  w = evalexp(son(e));
       if (shape_align(sh(e))!= 1) {
	  error(ERROR_INTERNAL, "should be align 1");
       }
       if (shape_size(sh(e))!= 32) {
	  w &= ((1 << shape_size(sh(e))) - 1);
       }
       return w;
    }
   case not_tag:
    {
       return ~evalexp(son(e));
    }
   case and_tag:
    {
       return evalexp(son(e)) & evalexp(bro(son(e)));
    }
   case or_tag:
    {
       return evalexp(son(e)) | evalexp(bro(son(e)));
    }
   case xor_tag:
    {
       return evalexp(son(e))^ evalexp(bro(son(e)));
    }

   case shr_tag:
    {
       return evalexp(son(e)) >> evalexp(bro(son(e)));
    }

   case shl_tag:
    {
       return evalexp(son(e)) << evalexp(bro(son(e)));
    }

   case concatnof_tag:
    {
       long  wd = evalexp(son(e));
       return wd | (evalexp(bro(son(e))) << shape_size(sh(son(e))));
    }

   case clear_tag:
    {
       if (shape_size(sh(e)) <= 32)
       return 0;
       break;
    }
   case env_offset_tag:
    {
       exp ident_exp = son(e);

       if (ismarked(ident_exp)) {
          long offval;
          switch (ptno(ident_exp)) {
          case var_pl:
             offval = -no(ident_exp) /8;
             break;
          case par2_pl:
             offval = no(ident_exp) /8;
             break;
          case par3_pl:
          case par_pl:
          default:
             offval = no(ident_exp) /8 + 8;
          }
          return offval;
       }
       break;
    }
   case env_size_tag:
    {
       dec * et = brog(son(son(e)));
       if (et -> dec_u.dec_val.processed)
       return et -> dec_u.dec_val.index;
       break;
    }
   case offset_add_tag:
    {
       return evalexp(son(e)) +evalexp(bro(son(e)));
    }
   case offset_max_tag:
    {
       long a = evalexp(son(e));
       long b = evalexp(bro(son(e)));
       return a > b ? a : b;
    }
   case offset_pad_tag:
    {
       return rounder(evalexp(son(e)), shape_align(sh(e)) / 8);
    }
   case offset_mult_tag:
    {
       return evalexp(son(e))*evalexp(bro(son(e)));
    }
   case offset_div_tag:
   case offset_div_by_int_tag:
    {
       long n = evalexp(bro(son(e)));
       if (n == 0) {
          n++;
          error(ERROR_SERIOUS, "evalexp: divide by zero");
       }
       return evalexp(son(e)) / n;
    }
   case offset_subtract_tag:
    {
       return evalexp(son(e)) -evalexp(bro(son(e)));
    }
   case offset_negate_tag:
    {
       return -evalexp(son(e));
    }
   case seq_tag:
    {
       if (name(son(son(e))) == prof_tag && last(son(son(e))))
	   return evalexp(bro(son(e)));
       break;
    }
   case cont_tag:
    {
       if (PIC_code && name(son(e)) == name_tag && isglob(son(son(e)))
           && son(son(son(e)))!= NULL
           && !(brog(son(son(e))) -> dec_u.dec_val.dec_var))
       return evalexp(son(son(son(e))));
       break;
    }
   }
   error(ERROR_SERIOUS, "Illegal constant expression in %s", ext_eval_name);
   return 0;
}

/*
    The expression e, representing an integer value, is evaluated.
*/

static void evalno
(exp e)
{
    mach_op *op;
    long sz = shape_size(sh(e));
    long k = evalexp(e);

    switch (sz) {

      case 8: {
	op = make_value(k & 0xff);
	eval_op(8L, op);
	return;
      }

      case 16: {
	op = make_value((k >> 8) & 0xff);
	eval_op(8L, op);
	op = make_value(k & 0xff);
	eval_op(8L, op);
	return;
      }

      case 32: {
	op = make_value((k >> 24) & 0xff);
	eval_op(8L, op);
	op = make_value((k >> 16) & 0xff);
	eval_op(8L, op);
	op = make_value((k >> 8) & 0xff);
	eval_op(8L, op);
	op = make_value(k & 0xff);
	eval_op(8L, op);
	return;
      }
      case 64: {
	flt64 bval;
	bval = exp_to_f64(e);
	op = make_value((bval.small>>24) & 0xff);
	eval_op(8L,op);
	op = make_value((bval.small>>16) & 0xff);
	eval_op(8L,op);
	op = make_value((bval.small>>8) & 0xff);
	eval_op(8L,op);
	op = make_value(bval.small & 0xff);
	eval_op(8L,op);

	op = make_value((bval.big>>24) & 0xff);
	eval_op(8L,op);
	op = make_value((bval.big>>16) & 0xff);
	eval_op(8L,op);
	op = make_value((bval.big>>8) & 0xff);
	eval_op(8L,op);
	op = make_value(bval.big & 0xff);
	eval_op(8L,op);
	return;
      }
    }
    error(ERROR_SERIOUS, "Illegal integer value in %s", ext_eval_name);
    return;
}


/*
    This routine converts the real constant e into an array of longs
    giving the bitpattern corresponding to this constant.  Although
    care has been taken, this may not work properly on all machines
    (although it should for all IEEE machines).  It returns NULL if
    it cannot convert the number sufficiently accurately.
*/

long *realrep
(exp e)
{
    int i, n, ex;
#if (FBASE == 10)
    double d, m;
#endif
    char bits[128];
    static long longs[4];
    int exp_bits, mant_bits;
    long sz = shape_size(sh(e));

    /* Find size of exponent and mantissa */
    if (sz == 32) {
	exp_bits = 8;
	mant_bits = 23;
    } else if (sz == 64) {
	exp_bits = 11;
	mant_bits = 52;
    } else {
	exp_bits = 15;
	mant_bits = 96 /* or 112? */ ;
    }

#if (FBASE == 10)

    if (!convert_floats) return NULL;

    if (name(e) == real_tag) {
	/* Calculate value */
	flt *f = flptnos + no(e);
	char fbuff[100];
	char *p = fbuff;
	if (f->exp <= DBL_MIN_10_EXP || f->exp >= DBL_MAX_10_EXP) {
	    /* Reject anything that won't fit into a double */
	    return NULL;
	}
	if (f->sign < 0)*(p++) = '-';
	*(p++) = '0' + f->mant[0];
	*(p++) = '.';
	for (i = 1; i < MANT_SIZE; i++)*(p++) = '0' + f->mant[i];
	sprintf(p, "e%d",(int)f->exp);
	d = atof(fbuff);
	if (sz == 32) {
	    /* Round floats */
	    static float fd;
	    fd = (float)d;
	    d = (double)fd;
	}
    } else {
	error(ERROR_SERIOUS, "Illegal floating-point constant");
	return NULL;
    }

    /* Deal with 0 */
    if (d == 0.0) {
	for (i = 0; i < sz / 32; i++)longs[i] = 0;
	return longs;
    }

    /* Fill in sign */
    if (d < 0.0) {
	bits[0] = 1;
	d = -d;
    } else {
	bits[0] = 0;
    }

    /* Work out mantissa and exponent */
    m = frexp(d, &ex);
    m = 2.0 * m - 1.0;
    ex--;

    /* Fill in mantissa */
    for (i = 1; i <= mant_bits; i++) {
	int j = exp_bits + i;
	m *= 2.0;
	if (m >= 1.0) {
	    m -= 1.0;
	    bits[j] = 1;
	} else {
	    bits[j] = 0;
	}
    }

#else

	UNUSED(mant_bits); /* only for FBASE 10 */

    if (name(e) == real_tag) {
	int j, k = -1;
	flt *f = flptnos + no(e);

	/* Deal with 0 */
	if (f->sign == 0) {
	    for (i = 0; i < sz / 32; i++)longs[i] = 0;
	    return longs;
	}

	/* Fill in sign */
	bits[0] = (f->sign < 0 ? 1 : 0);

	/* Work out exponent */
	ex = FBITS *(f->exp) + (FBITS - 1);

	/* Fill in mantissa */
	for (i = 0; i < MANT_SIZE; i++) {
	    for (j = FBITS - 1; j >= 0; j--) {
		if ((f->mant[i]) & (1 << j)) {
		    if (k >= 0) {
			if (k < sz)bits[k] = 1;
			k++;
		    } else {
			/* Ignore first 1 */
			k = exp_bits + 1;
		    }
		} else {
		    if (k >= 0) {
			if (k < sz)bits[k] = 0;
			k++;
		    } else {
			/* Step over initial zeros */
			ex--;
		    }
		}
	    }
	}

    } else {
	error(ERROR_SERIOUS, "Illegal floating-point constant");
	return NULL;
    }

#endif

    /* Fill in exponent */
    ex += (1 << (exp_bits - 1)) - 1;
    if (ex <= 0 || ex >= (1 << exp_bits) - 1) {
	if (check & CHECK_FLPT_OVERFLOW) {
	    error(ERROR_SERIOUS, "Floating point constant out of range");
	}
	if (sz == 32) {
	    if (bits[0])longs[0] = 0x80000000;
	    longs[0] += 0x7f800000;
	} else {
	    if (bits[0])longs[0] = 0x80000000;
	    longs[0] += 0x7ff00000;
	    longs[1] = 0;
	}
	return longs;
    }
    for (i = 0; i < exp_bits; i++) {
	int j = exp_bits - i;
	bits[j] = ((ex & (1 << i))? 1 : 0);
    }

    /* Convert bits to longs */
    n = (sz / 32) - 1;
    for (i = 0; i <= n; i++) {
	int j;
	long b0 = 0, b1 = 0, b2 = 0, b3 = 0;
	for (j = 0; j < 8; j++)b0 = 2 * b0 + bits[32 * i + j];
	for (j = 8; j < 16; j++)b1 = 2 * b1 + bits[32 * i + j];
	for (j = 16; j < 24; j++)b2 = 2 * b2 + bits[32 * i + j];
	for (j = 24; j < 32; j++)b3 = 2 * b3 + bits[32 * i + j];

	assert(endian == ENDIAN_BIG);
	longs[i] = (b0 << 24) + (b1 << 16) + (b2 << 8) + b3;
    }
    return longs;
}


/*
    The expression e, representing a real value, is evaluated.  There
    are two cases, depending on the flag convert_floats.  Either the
    number itself or its representation in bits is output.
*/

static void evalreal
(exp e)
{
    long *p;
    long sz = shape_size(sh(e));
    eval_instr();
    p = realrep(e);
    if (p) {
	int i;
	for (i = 0; i < sz / 32; i++) {
	    mach_op *op = make_value(p[i]);
	    eval_op(32L, op);
	}
    } else {
	flt *f = flptnos + no(e);
	mach_op *op = make_float_data(f);
	int instr = insf(sz, m_as_float, m_as_double, m_dont_know);
	make_instr(instr, op, NULL, 0);
	current_sz = 0;
    }
    return;
}


/*
    The next n bits are cleared, either by padding with zeros or by
    using a space instruction.
*/

static void clear_out
(long n, bool isconst, long al)
{
    mach_op *op;
    if (isconst) {
	while (n > 0) {
	    op = make_value(0);
	    eval_op(8L, op);
	    n--;
	}
    } else {
	eval_instr();
	current_sz = 0;
	if (n > 0) {
	  op = make_int_data(n);
	  make_instr(m_as_space, op, NULL, 0);
	}
	current_sz = 0;
    }
    return;
}


/*
    This is the main constant evaluation routine.  The expression e is
    evaluated.  al gives the alignment of e.
*/

void evalaux
(exp e, bool isconst, long al)
{
    switch (name(e)) {

	case real_tag: {
	    /* Real values */
	    evalreal(e);
	    return;
	}

	case compound_tag: {
	    /* Compound values - deal with each component */
	    exp val;
	    mach_op *op;
	    exp offe = son(e);
	    long off;
	    long work = 0;
	    long crt_off = 0;
	    long bits_left = 0;
            bool param_aligned = 0;

	    if (offe == NULL) return;

            /* look ahead to determine if it is parameter aligned */
            val = bro(offe);
            if (! last(val)) {
               offe = bro(val);
               if (offe->shf->sonf.ald->al.al_val.al == 32) {
                  param_aligned = 1;
               }
            }
            offe = son(e);

	    while (1) {
		off = no(offe);
		val = bro(offe);

		if (bits_left && off >= (crt_off + 8)) {
		    op = make_value((work >> 24) & 0xff);
		    eval_op(8L, op);
		    crt_off += 8;
		    work = 0;
		    bits_left = 0;
		}

		if (off < crt_off) {
		    error(ERROR_SERIOUS, "Compound constants out of order in %s",
			    ext_eval_name);
		}

		if (off > crt_off && !bits_left) {
		    clear_out((off - crt_off) / 8, 1, al);
		    crt_off = off;
		}

		if (name(sh(val))!= bitfhd) {
                   if (param_aligned) {
                      switch (name(sh(val))) {
                      case scharhd:
                      case ucharhd:
                         clear_out(3, 1, al);
                         crt_off += 3*8;
                         break;
                      case swordhd:
                      case uwordhd:
                         clear_out(2, 1, al);
                         crt_off += 2*8;
                         break;
                      }
                   }

		    evalaux(val, isconst,(crt_off + al) & 56);
		    crt_off += shape_size(sh(val));
		} else {
		    long sz = shape_size(sh(val));
		    long offn = off - crt_off;
		    long nx, enx;
		    long extra_byte = 0;
		    if (name(val) == val_tag) {
			nx = no(val);
		    } else {
			nx = no(son(val));
		    }
		    if (sz > 32 - offn) {
			enx = (nx & 0xff);
			extra_byte = 1;
			nx >>= 8;
			sz -= 8;
		    }
		    nx = (nx & lo_bits[sz]) << (32 - offn - sz);
		    work += nx;
		    bits_left = offn + sz;
		    while (bits_left >= 8) {
			long v;
			bits_left -= 8;
			v = (work >> 24) & 0xff;
			work <<= 8;
			if (extra_byte) {
			    bits_left += 8;
			    work += (enx << (32 - bits_left));
			    extra_byte = 0;
			}
			op = make_value(v);
			eval_op(8L, op);
			crt_off += 8;
		    }
		}

		if (last(val)) {
		    long left;
		    if (bits_left) {
			op = make_value((work >> 24) & 0xff);
			eval_op(8L, op);
			crt_off += 8;
		    }
		    left = shape_size(sh(e)) - crt_off;
		    if (left > 0)clear_out(left / 8, 1, al);
		    return;
		}
		offe = bro(val);
	    }
	    /* Not reached */
	}

	case name_tag: {
	    /* External names */
	    mach_op *op;
	    long n = no(e);
	    long sz = shape_size(sh(e));
	    char *nm = brog(son(e)) ->dec_u.dec_val.dec_id;
	    op = make_extern_data(nm, n / 8);
	    eval_op(sz, op);
	    return;
	}

	case string_tag: {
	    /* Strings */
	    long i;
	    long char_size = (long)props(e);
	    long n = shape_size(sh(e)) / char_size;
	    switch (char_size) {

		case 8: {
		    char *s = nostr(e);
		    for (i = 0; i < n; i++) {
			long ch = (long)s[i];
			eval_op(char_size, make_value(ch));
		    }
		    break;
		}

		case 16: {
		    short *s = (short *)nostr(e);
		    for (i = 0; i < n; i++) {
			long ch = (long)s[i];
			eval_op(char_size, make_value(ch));
		    }
		    break;
		}

		case 32: {
		    long *s = (long *)nostr(e);
		    for (i = 0; i < n; i++) {
			long ch = s[i];
			eval_op(char_size, make_value(ch));
		    }
		    break;
		}

		default : {
		    error(ERROR_SERIOUS, "Illegal string size in %s", ext_eval_name);
		    break;
		}
	    }
	    return;
	}

	case res_tag: {
	    /* Result values */
	    shape ss = sh(son(e));
	    long sz = shape_size(ss) / 8;
	    long sa = shape_align(ss);
	    clear_out(sz, isconst, sa);
	    return;
	}
      case top_tag:
      case null_tag: {
	    /* Null values */
	    shape ss = sh(e);
	    long sz = shape_size(ss) / 8;
	    long sa = shape_align(ss);
	    clear_out(sz, isconst, sa);
	    return;
	}

	case ncopies_tag: {
	    /* Multiple copies */
	    long i;
	    exp t = son(e);
	    long sa = shape_align(sh(t));
	    if (is_comm(t)) {
		long sz = rounder(shape_size(sh(t)), sa) / 8;
		clear_out(sz * no(e), isconst, sa);
		return;
	    }
	    for (i = 0; i < no(e); i++)evalaux(t, isconst, sa);
	    return;
	}

	case nof_tag: {
	    /* Array values */
	    exp t = son(e);
	    if (t == NULL) return;
	    while (1) {
		evalaux(t, isconst, al);
		if (last(t)) return;
		t = bro(t);
	    }
	    /* Not reached */
	}

	case concatnof_tag: {
	    /* Concatenated arrays */
	    long a2 = (al + shape_size(son(e))) & 63;
	    evalaux(son(e), isconst, al);
	    evalaux(bro(son(e)), isconst, a2);
	    return;
	}

	case chvar_tag:
	case int_to_bitf_tag: {
	    /* Change variety */
	    if (name(son(e)) == val_tag) {
		sh(son(e)) = sh(e);
		evalaux(son(e), isconst, al);
		return;
	    }
	    error(ERROR_SERIOUS, "Illegal change variety constant in %s", ext_eval_name);
	    return;
	}

	case chfl_tag: {
	    /* Change floating variety */
	    if (name(son(e)) == real_tag) {
		sh(son(e)) = sh(e);
		evalaux(son(e), isconst, al);
		return;
	    }
	    error(ERROR_SERIOUS, "Illegal change floating variety constant in %s",
		    ext_eval_name);
	    return;
	}

	case clear_tag: {
	    long sz = shape_size(sh(e)) / 8;
	    clear_out(sz, isconst, al);
	    return;
	}
#if 0
        case env_size_tag: {
           dec* d = brog(son(son(e)));
           mach_op* op = make_lab_data((long)d, 0);
           eval_op(32L,op);
           return;
        }

	case env_offset_tag: {
           /* Offsets */
           long offval;
           mach_op *op;
           exp ident_exp = son(e);
           op = make_lab_data((long)ident_exp, 0);
           eval_op(32L,op);

           return;
	}
#endif
	case ident_tag: {
	     /* Simple identifications */
	     exp body = bro(son(e));
	     if (name(body) == name_tag && son(body) == e) {
		evalaux(son(e), isconst, al);
		return;
	     }
	     break;
	}

	case minptr_tag: {
	    exp p1 = son(e);
	    exp p2 = bro(p1);
	    if (name(p1) == name_tag && name(p2) == name_tag) {
		long n = no(p1) - no(p2);
		long sz = shape_size(sh(e));
		char *n1 = brog(son(p1)) ->dec_u.dec_val.dec_id;
		char *n2 = brog(son(p2)) ->dec_u.dec_val.dec_id;
		mach_op *op1 = new_mach_op();
		mach_op *op2 = new_mach_op();
		mach_op *op3 = new_mach_op();
		op1->type = MACH_EXT;
		op1->def.str = n1;
		op1->plus = op2;
		op2->type = MACH_NEG;
		op2->plus = op3;
		op3->type = MACH_EXT;
		op3->def.str = n2;
		if (n) {
		    mach_op *op4 = new_mach_op();
		    op4->type = MACH_VAL;
		    op4->def.num = n;
		    op3->plus = op4;
		}
		eval_op(sz, op1);
		return;
	    }
	    break;
	}
	default:
            evalno(e);
    }
}


#if 0

/*
    If so it can be put into the common area.
*/

static int is_comm
(exp e)
{
    switch (name(e)) {

	case val_tag: return no(e) ? 0 : 1;

	case int_to_bitf_tag:
	case chvar_tag: return is_comm(son(e));

	case real_tag: {
	    flpt f = no(e);
	    return flptnos[f].sign ? 0 : 1;
	}

	case compound_tag: {
	    exp t = son(e);
	    if (t == NULL) return 1;
	    while (1) {
		t = bro(t);
		if (name(sh(t))!= bitfhd) {
		    if (!is_comm(t)) return 0;
		} else {
		    if (name(t) == val_tag) {
			if (no(t)) return 0;
		    } else {
			if (no(son(t))) return 0;
		    }
		}
		if (last(t)) return 1;
		t = bro(t);
	    }
	    /* Not reached */
	}

	case ncopies_tag: return is_comm(son(e));

	case nof_tag: {
	    exp t = son(e);
	    if (t == NULL) return 1;
	    while (1) {
		if (!is_comm(t)) return 0;
		if (last(t)) return 1;
		t = bro(t);
	    }
	    /* Not reached */
	}

	case concatnof_tag: {
	    exp t = son(e);
	    return is_comm(t) && is_comm(bro(t));
	}

	case clear_tag:
	case res_tag:
	case null_tag: return 1;
    }
    return 0;
}

#endif


/*
    OUTPUT A CONSTANT
*/

void evaluate
(exp c, long cname, char *s, int isconst, int global, diag_global *di)
{
    mach_op *op1, *op2;
    long al = (long)shape_align(sh(c));

    if (is_comm(c) ||
       ((name(c) == name_tag) && (son(son(c))) && (name(son(son(c))) == null_tag))) {

	long sz = rounder(shape_size(sh(c)), 32);

	/* Common global values */
	if (global && cname == -1 && !is_local(s)) {
	    op1 = make_extern_data(s, 0);
	    op2 = make_int_data(sz / 8);
	    make_instr(m_as_common, op1, op2, 0);

	    if (diag != DIAG_NONE && di)xdb_diag_val_begin(di, s, cname, global);

	    return;
	}

	if (asm_uses_lcomm) {
	    /* Common local value */
	    if (cname == -1) {
	        op1 = make_extern_data(s, 0);
	    } else {
	        op1 = make_lab_data(cname, 0);
	    }
	    op2 = make_int_data(sz / 8);
	    make_instr(m_as_local, op1, op2, 0);

	    if (diag != DIAG_NONE && di)xdb_diag_val_begin(di, s, cname, global);
	} else {
	    /* Common local value */
	    area(pbss);
	    if (cname == -1) {
	         make_external_label(s);
	    } else {
	         make_label(cname);
	    }

	    if (diag != DIAG_NONE && di)xdb_diag_val_begin(di, s, cname, global);

	    op1 = make_int_data(sz / 8);
	    make_instr(m_as_space, op1, NULL, 0);
	}

	return;
    }

    /* Data values */
    if (global && cname == -1 && !is_local(s)) {
	op1 = make_extern_data(s, 0);
	make_instr(m_as_global, op1, NULL, 0);
    }

    if (diag != DIAG_NONE && di)xdb_diag_val_begin(di, s, cname, global);

    if (al <= 32)al = 32;

    ext_eval_name = "statically declared object";
    if (cname == -1) {
	make_external_label(s);
	if (!is_local(s))ext_eval_name = s;
    } else {
	make_label(cname);
    }
    evalaux(c,(bool)isconst, al);
    eval_instr();
    return;
}

