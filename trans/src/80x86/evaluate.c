/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>

#include <local/diag_config.h>
#include <local/out.h>
#include <local/codermacs.h>

#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/table_fns.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/flpt.h>
#include <construct/install_fns.h>
#include <construct/machine.h>
#include <construct/f64.h>

#include <main/flags.h>

#ifdef NEWDIAGS
#include <newdiag/diag_fns.h>
#else
#include <diag/diag_fns.h>
#endif

#include "localtypes.h"
#include "coder.h"
#include "instr.h"
#include "instr386.h"
#include "assembler.h"
#include "messages_8.h"
#include "evaluate.h"
#include "localexpmacs.h"


/* PROCEDURES */


static void outsize
(int n)
{
  switch ((n+7) /8) {
    case 1:
	outbyte();
	break;
    case 2:
	outshort();
	break;
    default:
	outlong();
	break;
  };
  return;
}


long  evalexp
(exp e)
{
  switch (name(e)) {
    case  val_tag:
    case null_tag:
    case top_tag:
      {
	if (name(sh(e)) == offsethd && al2(sh(e)) >= 8) {
		return no(e) >> 3;
	}
        return no(e);
      }
    case bitf_to_int_tag:
      {
	return evalexp(son(e));
      }
    case int_to_bitf_tag:
      {
	long  w = evalexp(son(e));
	if (shape_align(sh(e))!= 1) {
	  failer("should be align 1");
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
	if (name(son(e)) == 0)
   	  return no(son(e)) / 8;
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
    	return evalexp(son(e)) /evalexp(bro(son(e)));
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
  failer(BAD_VAL);
  return 0;
}


/* outputs a value */
static void evalval
(exp e)
{
  int e_size = shape_size(sh(e));
  unsigned char  n = name(e);
  int ov;

  if (n == val_tag) {
    int k = (name(sh(e)) == offsethd && al2(sh(e))!= 1)
                  ? no(e) /8 : no(e);
    flt64 x;
    if (isbigval(e)) {
      x = flt_to_f64(k, is_signed(sh(e)), &ov);
      k = x.small;
    }
    switch (e_size) {
      case 8:
	outn((long)k & 0xff);
	break;
      case 16:
	outn((long)k & 0xffff);
	break;
      case 32:
	outn((long)k);
	break;
      case 64:
	outn((long)k);
	outs(", ");
	if (isbigval(e)) {
	  SET(x);
	  outn((long)x.big);
	} else
	if (is_signed(sh(e)) && k < 0)
	  outn((long) -1);
	else
	  outn((long)0);
	break;
      default:
	outn((long)k);
	break;
    };
    return;
  };

  if (n == real_tag) {
    outreal(e);
    return;
  };

  if (n == reff_tag && name(son(e)) == name_tag && isglob(son(son(e)))) {
    outopenbr();
    outs(brog(son(son(e))) -> dec_u.dec_val.dec_id);
    outs(" + ");
    outn((long)(no(e) + no(son(e))) / 8);
    outclosebr();
    return;
  };

  if (n == name_tag) {
    if (no(e)!= 0) {
      outopenbr();
      outs(brog(son(e)) -> dec_u.dec_val.dec_id);
      outs(" + ");
      outn((long)no(e) / 8);
      outclosebr();
    }
    else
      outs(brog(son(e)) -> dec_u.dec_val.dec_id);
    return;
  };

  {
    int k = evalexp(e);
    switch (e_size) {
      case 8:
	outn((long)k & 0xff);
	break;
      case 16:
	outn((long)k & 0xffff);
	break;
      case 32:
	outn((long)k);
	break;
      default:
	outn((long)k);
	break;
    };
  }
  return;
}



/* auxiliary for evalaux */
static  void clear_out
(int n, int isconst, int al)
{
  if (n == 0)
     return;

  if (isconst) {
    while (al >= 32 && n >= 4) {
      outlong();
      outs("0");
      outnl();
      n -= 4;
    };
    while (n > 0) {
      outbyte();
      outs("0");
      outnl();
      --n;
    };
  }
  else {
    outs(".set .,.+");
    outn((long)n);
    outnl();
  };

  return;
}

/* does the work of outputting of constants recursively */
static void evalaux
(exp e, int isconst, int al)
{
  int e_size = shape_size(sh(e));
  unsigned char  n = name(e);

  if (n == compound_tag) {		/* output components in turn */
    int work = 0;
    exp offe;
    exp val;
    int bits_left = 0;
    int crt_off = 0;
    int off, offn, sz, nx, i;

    if (son(e) == NULL)
      return;

    offe = son(e);

    while (1)
     {
       off = no(offe);
       val = bro(offe);
       if (bits_left &&
            off >= (crt_off + 8))
         {
	    outbyte();
	    outn((long)work & 0xff);
            outnl();
            crt_off += 8;
            work = 0;
            bits_left = 0;
         };

       if (off < crt_off)
              failer(CPD_ORDER);
       if (off >= (crt_off + 8))
           {
              clear_out((off-crt_off) /8, isconst, al);
              crt_off = off & -8;
           };

       if (name(sh(val))!= bitfhd)
         {
           evalaux(val, isconst,(crt_off + al) & 56);
           crt_off += shape_size(sh(val));
         }
       else
         {
           offn = off - crt_off;
           sz = shape_size(sh(val));
           nx = (name(val) ==int_to_bitf_tag)? no(son(val)): no(val);
           work += nx << offn;
           bits_left = offn+sz;
           if ((offn + sz) <= 32)
              { while ((offn+sz) >= 8)
                 {
	           outbyte();
	           outn((long)work & 0xff);
                   outnl();
                   crt_off += 8;
                   work >>= 8;
                   offn -= 8;
                   bits_left = offn+sz;
                 };
               work &= ((1 << bits_left) - 1);
              }
           else
            {
              for (i=0; i<4; ++i)
                 {
	           outbyte();
	           outn((long)work & 0xff);
                   outnl();
                   crt_off += 8;
                   work >>= 8;
                   offn -= 8;
                   bits_left = offn+sz;
                 };
               work = nx >> bits_left;
             };
         };

       if (last(val))   /* CLEAR OUT SHAPE size_shape(e) - crt_off */
        {
          if (bits_left)
            {
	       outbyte();
	       outn((long)work & 0xff);
               outnl();
               crt_off += 8;
            };
          clear_out((shape_size(sh(e)) - crt_off) /8, isconst,
			8);
          return;
        };
       offe = bro(val);
     };
  };
	/*
	 * String constants
	 */
	if (n == string_tag) {
		char *s = nostr(e);
		int goon; /* Go on */
		int i, j;
		int char_size = (int)string_char_size(e);

		/* Total number of chars */
		goon = shape_size(sh(e)) / char_size;

#if 0
		{
			char *c = s;

			out_comment();
			outs("string constant: ");
			do {
				switch (*c) {
				case '\n':
					outs("\\n");
					break;
				case '\0':
					outs("\\0");
					break;
				default:
					outc(*c);
				}

			} while (*c++ != '\0');
			outs("\n");
		}
#endif

		/* 10 chars per line */
		for (i = 0; goon; i += 10) {
			switch (char_size) {
			case 8:	outbyte(); break;
			case 16: outshort(); break;
			case 32: outlong(); break;
			case 64: outlong(); break;
			}

			for (j = i; goon && j < i + 10; ++j) {
				switch (props(e)) {
				case 8:
					outn((long)s[j]);
					break;
				case 16:
					outn((long)((short*)(void*)s)[j]);
					break;
					 /* the pun to short* is correct: jmf */
				case 32:
					outn((long)((int*)(void*)s)[j]);
					break;
					 /* the pun to int* is correct: jmf */
				case 64: {
						 flt64 x;
						 int ov;
						 x = flt_to_f64(
						     ((int*)(void*)s)[j],
						     0,
						     &ov);
						 outn((long)x.small);
						 outs(", ");
						 outn((long)x.big);
					 }
				}

				--goon;
				if (goon && j < i + 9)
					outs(", ");
			}
			outnl();
		}
		return;
	}

  if (n == res_tag) {
    int  nb;
    nb = shape_size(sh(son(e))) / 8;
    clear_out(nb, isconst, shape_align(sh(son(e))));
    return;
  };

  if (n == ncopies_tag) {
    int  m = no(e);
    int  sz, i;
    exp val = son(e);
    while (name(val) == ncopies_tag) {
	m *= no(val);
	val = son(val);
    }
    sz = shape_size(sh(val)) / 8;
    if ((name(val) == null_tag ||
	 name(val) == val_tag) && !isbigval(val) && no(val) == 0)
      clear_out(m * sz, isconst, shape_align(sh(val)));
    else {
      for (i = 0; i < m; i++)
	evalaux(val, isconst, al);
    }
    return;
  };

  if (n == nof_tag)
   {
     exp t = son(e);
     if (t == NULL)
       return;
     while (1)
      {
        evalaux(t, isconst, al);
        if (last(t))
          return;
        t = bro(t);
        dot_align((shape_align(sh(t)) <=8)? 1 : shape_align(sh(t)) /8);
      };
   };

  if (n == concatnof_tag) {
    evalaux(son(e), isconst, al);
    evalaux(bro(son(e)), isconst,(al +shape_size(son(e))) & 63);
    return;
  };

  if (n == clear_tag)
   {
     int sz = shape_size(sh(e)) / 8;
     clear_out(sz, isconst, al);
     return;
   };

  if (n == chvar_tag && shape_size(sh(e)) == shape_size(sh(son(e)))) {
    sh(son(e)) = sh(e);
    evalaux(son(e), isconst, al);
    return;
  };


  outsize(e_size);
  evalval(e);
  outnl();
  return;
}

/* output a constant of given label number
   cname, or identifier s cname==-1 means
   use s */
void evaluate
(exp c, int cname, char *s, int isconst, int global, diag_global * diag_props)
{
  int al = shape_align(sh(c));

  if (global && cname == -1) {
    outs(".globl ");
    outs(s);
    outnl();
  };

  if (name(sh(c)) == realhd ||
       (name(sh(c)) == nofhd && ptno(sh(c)) == realhd) ||
      shape_size(sh(c)) >= 512)
    al = 64;

  if (al <= 8)
    dot_align(4);
  else
    dot_align(al/8);

  if (diag_props)
#ifdef NEWDWARF
    DIAG_VAL_BEGIN(diag_props, global, cname, s);
#else
    diag_val_begin(diag_props, global, cname, s);
#endif

  if (cname == -1) {
    outs(s);
  }
  else {
    outs(local_prefix);
    outn((long)cname);
  };

  outs(":");
  outnl();

  evalaux(c, isconst, al);

  if (global)
    eval_postlude(s, c);

  outnl();

  if (diag_props) {
#ifdef NEWDWARF
    DIAG_VAL_END(diag_props);
#else
    diag_val_end(diag_props);
#endif
  }

  return;
}
