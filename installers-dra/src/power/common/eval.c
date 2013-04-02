/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*****************************************************************
		eval.c

	The main procedure defined here is evaluated which outputs
assembler for data. The parameters are an evaluated exp and an index
into the table of externals (or 0 meaning anonymous).
*****************************************************************/

#include <ctype.h>
#include <stdio.h>

#include <shared/error.h>

#include <construct/flpttypes.h>
#include <construct/flpt.h>
#include <construct/machine.h>
#include <construct/f64.h>

#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "maxminmacs.h"
#include "translat.h"
#include "comment.h"
#include "eval.h"
#include "frames.h"

extern FILE *as_file;

long correct_shape(long, int);

/* various pieces of info for outputting data depending on shape */
static	mm scmm	=	{127,		-128,		"\t.byte\t%ld\n"};
static	mm uscmm =	{255,		0,		"\t.byte\t%ld\n"};
static	mm shmm	=	{0x7fff,	0xffff8000,	"\t.short\t%ld\n"};
static	mm ushmm =	{0xffff,	0,		"\t.short\t%ld\n"};
static	mm swmm	=	{0x7fffffff,	0x80000000,	"\t.long\t%ld\n"};
static	mm uswmm =	{0xffffffff,	0,		"\t.long\t%ld\n"};


/* number for anonymous label in data space - L.Dnnn */
int next_data_lab(void)
{
  static int data_lab = 100;

  return ++data_lab;
}


/*************************************************************
maxmin

finds the data size from the range of an integer shape
**************************************************************/
mm maxmin(shape s)
{
  switch (name(s))
  {
  case scharhd:
    return scmm;
  case ucharhd:
    return uscmm;
  case swordhd:
    return shmm;
  case uwordhd:
    return ushmm;
  case slonghd:
    return swmm;
  case ulonghd:
    return uswmm;
  default:
    return uswmm;
  }

}


/**************************************************************
outlab

outputs the label parameter if non negative else interprets it
to be an index into the externals and outputs the identifier.
**************************************************************/

void outlab(int l)
{
  fprintf(as_file, "%s", ext_name(l));
}

/* translate time evaluate integer exp 'e' */
long evalexp(exp e)
{
  switch (name(e))
  {
   case null_tag:case top_tag:
    return 0;
   case val_tag:
    {
      /* offsets appear as bits, but are converted to bytes if alignment
       is not bits */
      if (name(sh(e)) == offsethd && al2(sh(e)) >= 8)
      {
	return no(e) >>3;
      }
      return no(e);
    }
    case env_size_tag:
    {
      exp tg = son(son(e));
      procrec *pr = &procrecs[no(son(tg))];
      return ((pr->frame_size) >>3) + pr->max_callee_bytes;
    }
    case offset_add_tag: {
      return evalexp(son(e)) + evalexp(bro(son(e)));
    }
    case offset_max_tag: {
      return max(evalexp(son(e)),evalexp(bro(son(e))));
    }
    case offset_pad_tag: {
      return rounder(evalexp(son(e)),shape_align(sh(e)));
    }
    case offset_mult_tag: {
      return evalexp(son(e))*evalexp(bro(son(e)));
    }
    case offset_div_tag:
    case offset_div_by_int_tag: {
      return evalexp(son(e)) /evalexp(bro(son(e)));
    }
    case offset_subtract_tag: {
      return evalexp(son(e)) -evalexp(bro(son(e)));
    }
    case offset_negate_tag: {
      return -evalexp(son(e));
    }


   case chvar_tag:
    {
      return correct_shape(evalexp(son(e)),name(sh(e)));
    }
   case bitf_to_int_tag:
    {
      return evalexp(son(e));
    }

   case int_to_bitf_tag:
    {
      ash a;
      unsigned long w = evalexp(son(e));

      a = ashof(sh(e));
      if (a.ashalign != 1)
      {
	fail("should be align 1");
      }
      if (a.ashsize != 32)
      {
	w &= ((1 << a.ashsize) - 1);
      }
      return w;
    }
   case not_tag:
    {
      return correct_shape(~evalexp(son(e)),name(sh(e)));
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
      return evalexp(son(e)) ^ evalexp(bro(son(e)));
    }

   case shr_tag:
    {
      bool sgned = is_signed(sh(e));
      long sl;
      unsigned long ul;
      if (sgned)
      {
	sl = (long)correct_shape(evalexp(son(e)),name(sh(e)));
	return sl >> evalexp(bro(son(e)));
      }
      else
      {
	ul = (unsigned long)correct_shape(evalexp(son(e)),name(sh(e)));
	return ul >> evalexp(bro(son(e)));
      }
    }

  case shl_tag:
    {
      return correct_shape(evalexp(son(e)) <<evalexp(bro(son(e))),name(sh(e)));
    }

  case concatnof_tag:
    {
      unsigned long w_lhs = evalexp(son(e));
      unsigned long w_rhs = evalexp(bro(son(e)));
      ash ash_lhs, ash_rhs;
      ash_lhs = ashof(sh(son(e)));
      ash_rhs = ashof(sh(bro(son(e))));

      ASSERT(ash_lhs.ashalign==1 && ash_lhs.ashsize<=32);
      ASSERT(ash_rhs.ashalign==1 && ash_rhs.ashsize<=32);
      ASSERT(ash_lhs.ashsize+ash_rhs.ashsize<=32);

      FULLCOMMENT4("evalexp() concatnof_tag: lhs,rhs=%#x,%#x ash(rhs) =%d,%d",
		w_lhs, w_rhs, ash_rhs.ashalign, ash_rhs.ashsize);

      if (ash_rhs.ashsize == 32)
      {
	/* avoid illegal shift by 32 */
	ASSERT(w_lhs==0);
	return w_rhs;
      }
      return (w_lhs << ash_rhs.ashsize) | w_rhs;
    }

  case clear_tag:
    {
      ash a;

      a = ashof(sh(e));

      FULLCOMMENT2("evalexp() clearshape_tag: ash=%d,%d", a.ashalign, a.ashsize);
      if (a.ashsize > 32)
	fail("clear for more than 32 bits");

      return 0;
    }

   case env_offset_tag:
   case general_env_offset_tag:
    {
      return frame_offset(son(e));
    }

  default:
    COMMENT1("tag not in evalexp: %d", name(e));
    fail("tag not in evalexp");
    return 0;
  }
  /*NOTREACHED*/
}



struct concbittypet {
  int			bitposn;
  int			value_size;
  unsigned long		value;
};
typedef struct concbittypet	concbittype;


static concbittype emptyconcbit(int bitposn)
{
  concbittype start;

  start.bitposn = bitposn;
  start.value_size = 0;
  start.value = 0;

  return start;
}


static void outconcbit(concbittype c)
{
  unsigned long w = c.value;
  int bytes = (c.value_size + 7) / 8;
  int i;

  COMMENT2("outconcbit: bits=%d w=%#lx", c.value_size, w);

  if (c.value_size==0)
    return;			/* avoid .byte with no data */

  ASSERT(c.value_size<=32);

  /* to left end of word */
  if (c.value_size != 32)
    w = w << (32-c.value_size);

  /* POWER assembler only permits .long for 32-bit aligned values */

  /* output enough bytes */
  fprintf(as_file, "\t.byte\t");
  for (i = 0; i < bytes; i++)
  {
    if (i != 0)
      fprintf(as_file, ",");
    fprintf(as_file, "%#lx",(w >> 24) & 255);
    w = w << 8;
  }
  fprintf(as_file, "\n");
  ASSERT(w == 0);
}
/*
  Output a unary representation of the number val.  val should be
  less than or equal to 31 as it represent the number of bits
  in a bitfield which does not occupy a whole machine word.
*/
long unary(int val)
{
  int loop;
  long result=0;
  ASSERT(val <=31);
  for (loop=0;loop<val;++loop)
  {
    result <<=1;
    result |= 1;
  }
  return result;
}



static concbittype addconcbitaux(unsigned long w, int size, concbittype before)
{
  int wordbitposn;			/* 0..32 bit position in current word,
					 * 0 only at start of bit sequence */

  if (before.value_size==32 || (before.value_size != 0 && (before.bitposn&31) ==0))
  {
    ASSERT((before.bitposn&31) ==0);
    wordbitposn = 32;
  }
  else
  {
    wordbitposn = (before.bitposn&31);
  }

  FULLCOMMENT2("addconcbitaux() sz=%d w=%d",
	       size, w);
  FULLCOMMENT4("\tbefore=%d(%d) %#x:%d",
	       before.bitposn, wordbitposn, before.value, before.value_size);
#if 0
  ASSERT(size>0);		/* no longer have to handle zero for C */
#endif
  ASSERT(size<=32);

  ASSERT(before.value_size<=32);
  ASSERT(wordbitposn==0 || before.value_size<=wordbitposn);

  if (
     (size == 0 && (wordbitposn != 0 || before.value_size != 0))
      ||
     (wordbitposn + size > 32)
     )
  {
    /*
     * C zero size bitfield, align to word boundary; or
     * would go over word boundary, so output before and padding.
     */
    int pad_bits = 32 - wordbitposn;

#if 1
    ASSERT(pad_bits==0);		/* padding should now be explicit */

    before.value_size += pad_bits;
    before.value <<= pad_bits;
#endif

    outconcbit(before);

    /* clear before, as it has been output */
    before.bitposn += pad_bits;
    before.value_size = 0;
    before.value = 0;

    /* should be at word boundary */
    ASSERT((before.bitposn&31) ==0);
  }

  if (size == 0)
    return before;

  /* add to before */
  before.bitposn += size;
  before.value_size += size;
  if (size == 32)
    before.value = w;
  else
    before.value = (before.value << size) | (w & unary(size));

  FULLCOMMENT4("\t after=%d(%d) %#x:%d",
	       before.bitposn, wordbitposn, before.value, before.value_size);

  ASSERT(before.value_size<=32);

  return before;
}


static concbittype evalconcbitaux(exp e, concbittype before)
{
  switch (name(e))
  {
  case concatnof_tag:
    {
      concbittype lhs, rhs;
      lhs = evalconcbitaux(son(e), before);
      rhs = evalconcbitaux(bro(son(e)), lhs);

      return rhs;
    }

  default:
    {
      ASSERT(shape_align(sh(e)) ==1);

      return addconcbitaux(evalexp(e), shape_size(sh(e)), before);
    }
  }
}


static void evalconcbit(exp e, int bitposn)
{
  concbittype start;
  start = emptyconcbit(bitposn);

  outconcbit(evalconcbitaux(e, start));
}



static void set_align(int al)
{
  /* output .align if needed */
  switch (al)
  {
  case 0:
  case 1:
  case 8:
    break;

  case 16:
    fprintf(as_file, "\t.align\t1\n");
    break;

  case 32:
    fprintf(as_file, "\t.align\t2\n");
    break;

  case 64:
    fprintf(as_file, "\t.align\t3\n");
    break;

  default:
    fail("unexpected alignment");
  }
}



static void evalone(exp e, int bitposn)
{
  ash a;

  a = ashof(sh(e));

  COMMENT4("evalone: name(e) =%d, bitposn=%d, ash=%d,%d", name(e),
	   bitposn, a.ashsize, a.ashalign);
  COMMENT1("evalone no(e) =%d",no(e));

  set_align(a.ashalign);

  /* align bitposn */
  if (a.ashalign != 0)
  {
    bitposn = (bitposn / a.ashalign)* a.ashalign;
  }

  /* generate data initialiser for e */
  switch (name(e))
  {
   case string_tag:
    {
      long char_size = props(e);	/* bits width of each output char */
      long strsize = shape_size(sh(e)) / char_size;
      unsigned char *st = (unsigned char *)nostr(e);
      int i;

      if (char_size != 8)
      {
	/* wide chars, generate a .XXX line for each */
	for (i = 0; i <strsize; i++)
	{
	  unsigned int c;
	  char *directive;

	  switch (char_size)
	  {
	   case 16:
	    c = ((unsigned short *)st)[i];
	    directive = ".short";
	    break;
	   case 32:
	    c = ((unsigned int *)st)[i];
	    directive = ".long";
	    break;
	    /* +++ case 64 ??? */
	   default:
	    fail("unexpected wide char data width");
	  }
	  fprintf(as_file, "\t%s\t%#x\n", directive, c);
	}

	return;
      }

      /* output as ascii where possible for the human reader */
      while (strsize > 0)
      {
	int c = *st;

	if (c >= 32 && c < 127)
	{
	  fprintf(as_file, "\t.byte\t\"");
	  for (i = 0; strsize > 0 && i < 48 && c >= 32 && c < 127; i++)
	  {
	    if (c != '"')
	      putc(c, as_file);
	    else
	      fprintf(as_file, "\"\"");		/* " represented as "" */

	    st++;
	    strsize--;
	    c = *st;
	  }

	  fprintf(as_file, "\"\n");
	}
	else
	{
	  fprintf(as_file, "\t.byte\t");

	  for (i = 0; strsize > 0 && i < 16 && !(c >= 32 && c < 127); i++)
	  {
	    if (i != 0)
	      fprintf(as_file, ",");

	    fprintf(as_file, "%d", c);

	    st++;
	    strsize--;
	    c = *st;
	  }

	  fprintf(as_file, "\n");
	}
      }
      return;
    }

  case real_tag:
    {
      flt *f = flptnos + no(e);
      r2l v;

      if (a.ashsize==32)
      {
	v=real2longs_IEEE(f,0);
	fprintf(as_file,"\t.long\t");
	fprintf(as_file,"%ld",(long)v.i1);
      }
      else if (a.ashsize==64)
      {
	v=real2longs_IEEE(f,1);
	fprintf(as_file,"\t.long\t");
	fprintf(as_file,"%ld",(long)v.i2);
	fprintf(as_file,",");
	fprintf(as_file,"%ld",(long)v.i1);
      }
      else
      {
	v=real2longs_IEEE(f,2);
	fprintf(as_file,"\t.long\t");
	fprintf(as_file,"%ld",(long)v.i4);
	fprintf(as_file,",");
	fprintf(as_file,"%ld",(long)v.i3);
	fprintf(as_file,",");
	fprintf(as_file,"%ld",(long)v.i2);
	fprintf(as_file,",");
	fprintf(as_file,"%ld",(long)v.i1);
      }
      fprintf(as_file, "\n");
      return;
    }
   case null_tag:case top_tag:
    no(e) = 0;
    /* FALLTHROUGH */
   case val_tag:
    {
      char *asdata;

      FULLCOMMENT1("evalone() val_tag: %d", val_tag);

      /* allow 64 bit integers */
      if (shape_size(sh(e)) >32)
      {
	flt64 temp;
	int ov;
	if (isbigval(e))
	{
	  temp = flt_to_f64(no(e), 0, &ov);
	}
	else
	{
	  temp.big = (is_signed(sh(e)) && no(e) <0)?-1:0;
	  temp.small = no(e);
	}
	fprintf(as_file,"\t.long\t%ld\n",(long)temp.small);
	fprintf(as_file,"\t.long\t%ld\n",(long)temp.big);
	return;
      }
      /* allow for bitfields */
      if (a.ashalign == 1)
      {
	evalconcbit(e, bitposn);
	return;
      }

      if (a.ashalign <= 8)
      {
	asdata = ".byte";
      }
      else if (a.ashalign <= 16)
      {
	asdata = ".short";
      }
      else
      {
	asdata = ".long";
      }
      fprintf(as_file, "\t%s\t%ld\n", asdata, evalexp(e));
      return;
    }
  case name_tag:
    {
      dec *globdec = brog(son(e));
      char *nm = globdec->dec_u.dec_val.dec_id;

      ASSERT(isglob(son(e)));

      /* no() is offset */
      if (no(e) == 0)
      {
	fprintf(as_file, "\t.long\t%s\n", nm);
      }
      else
      {
	fprintf(as_file, "\t.long\t%s+%ld\n", nm,(long)(no(e) /8));
      }

      return;
    }

  case compound_tag:
    {
      /*
       * There is a lot of history in the following code, dating from
       * when tuples were without specified offsets for each field.
       * Really, this code should be totally rewritten.
       */
      exp off = son(e);
      exp tup = bro(off);
      ash tupa;
      concbittype remainderbits;
      long last_offset = 0;
      long last_align = 0;
      tupa = ashof(sh(tup));
      remainderbits = emptyconcbit(bitposn);

      /* output elements of aggregate recursively */
      while (1)
      {
	int gap = no(off) - remainderbits.bitposn;

	COMMENT4("evalone compound_tag: gap=%d off=%d ash=%d,%d",
		gap, no(off), tupa.ashsize, tupa.ashalign);

	/* check that component's alignment matches offset in struct */
	ASSERT((no(off) /tupa.ashalign)*tupa.ashalign <= no(off));

	/* and is no greater that struct's alignment */
	ASSERT(tupa.ashalign<=maxalign);

	if (no(off) < last_offset)
	  fail("eval compound_tag: not ascending order");

	if (last_align <= 1 || tupa.ashalign <= 1 || gap >= tupa.ashalign)
	{
	  /* gap can be bigger than 32, but addconcbitaux can only handle <= 32 */
	  while (gap > 0)
	  {
	    remainderbits = addconcbitaux(0, 1, remainderbits);
	    gap--;
	  }
	}
	else
	{
	  /* alignment will handle gap */
	  remainderbits.bitposn = ((remainderbits.bitposn + (tupa.ashalign-1)) / tupa.ashalign)* tupa.ashalign;
	}

	last_offset = no(off);
	last_align = tupa.ashalign;

	ASSERT(remainderbits.bitposn - bitposn == no(off));

	/* consecutive bitfields must be collected together for .byte */
	if (tupa.ashalign == 1)
	{
	  remainderbits = evalconcbitaux(tup, remainderbits);
	}
	else
	{
	  /* output final bits from any previous field */
	  outconcbit(remainderbits);
	  remainderbits = emptyconcbit(remainderbits.bitposn);

	  evalone(tup, remainderbits.bitposn);
	  remainderbits.bitposn += tupa.ashsize;
	}

	if (last(tup))
	{
	  /* output final bits from any previous field */
	  long databits = no(off) + tupa.ashsize;
	  long trailing_bytes = (a.ashsize-databits) / 8;

	  outconcbit(remainderbits);

	  ASSERT(a.ashsize >= databits);

	  /* pad out trailing unitialised space, eg union */
	  if (a.ashsize > databits && trailing_bytes > 0)
	  {
	    fprintf(as_file, "\t.space\t%d\n",(int)trailing_bytes);
	  }
	  return;
	}

	off = bro(bro(off));
	ASSERT(!last(off));
	tup = bro(off);

	tupa = ashof(sh(tup));
      }
      /*NOTREACHED*/
    }

  case nof_tag:
    {
      exp s = son(e);

      for (;;)
      {
	evalone(s, bitposn);
	if (last(s))
	  return;
	s = bro(s);
      }
      /*NOTREACED*/
    }

  case ncopies_tag:
    {
      int n = no(e);
      ash copya;
      int bitsize;
      int i;

      COMMENT1("ncopies_tag: n=%d", n);

      while (name(son(e)) == ncopies_tag)
      {
	e = son(e);
	n *= no(e);
      }

      e = son(e);
      copya = ashof(sh(e));
      if (copya.ashalign != 0)
	bitsize = (copya.ashsize / copya.ashalign)* copya.ashalign;
      else
	bitsize = 0;		/* probably never happen! */

      for (i = 0; i < n; i++)
      {
	COMMENT3("ncopies_tag: i=%d n=%d bitposn=%d", i, n, bitposn);
	evalone(e, bitposn);
	bitposn += bitsize;
      }
      return;
    }

  case concatnof_tag:
    {
      COMMENT2("concatnof_tag: ashalign=%d, ashsize=%d", a.ashalign, a.ashsize);

      /* allow for bitfields */
      if (a.ashalign == 1)
      {
	evalconcbit(e, bitposn);
      }
      else
      {
	ash a;

	a = ashof(sh(son(e)));
	evalone(son(e), bitposn);
	bitposn += a.ashsize;

	a = ashof(sh(bro(son(e))));
	if (a.ashalign != 0)
	  bitposn = (bitposn / a.ashalign)* a.ashalign;
	evalone(bro(son(e)), bitposn);
      }
      return;
    }

  case clear_tag:
    {
      /* allow for bitfields */
      if (a.ashalign == 1)
      {
	evalconcbit(e, bitposn);
	return;
      }

      fprintf(as_file, "\t.space\t%ld\n",(a.ashsize + 7) >> 3);
      return;
    }

   case not_tag:
   case and_tag:
   case or_tag:
   case shl_tag:
   case shr_tag:
   case bitf_to_int_tag:
   case int_to_bitf_tag:
   case chvar_tag:
    case env_offset_tag:case env_size_tag:
    case general_env_offset_tag:
    case offset_add_tag: case offset_max_tag:
    case offset_pad_tag: case offset_mult_tag: case offset_div_tag:
    case offset_div_by_int_tag: case offset_subtract_tag:
    case offset_negate_tag:

    {
      fprintf(as_file, "\t.long\t%ld\n", evalexp(e));
      return;
    }
   case minptr_tag:
    {
      exp p1 = son(e);
      exp p2 = bro(p1);
      if (name(p1) ==name_tag && name(p2) ==name_tag)
      {
	long n = no(p1) -no(p2);
	char *n1 = brog(son(p1)) ->dec_u.dec_val.dec_id;
	char *n2 = brog(son(p2)) ->dec_u.dec_val.dec_id;
	fprintf(as_file,"\t.long\t(%s-%s)",n1,n2);
	if (n<0)
	{
	  fprintf(as_file,"%ld",n);
	}
	else if (n>0)
	{
	  fprintf(as_file,"+%ld",n);
	}
	fprintf(as_file,"\n");
      }
      return;
    }

   default:
    COMMENT1("tag not in evaluated: %d", name(e));
    fail("illegal constant");
  }				/* end switch */
}



/*
 * Outputs data initialisers for the evaluated exp.
 * The result is the instore "address" of the constant.
 * A negative l implies that this is the initialisation of a global variable.
 */
instore evaluated(exp e, int l)
{
  int lab = (l == 0)? next_data_lab():(l < 0)? l : -l;
  instore isa;
  ash a;
  char *extname = ext_name(lab);
  a = ashof(sh(e));


  isa.adval = 0;
  isa.b.offset = 0;
  isa.b.base = lab;


  ASSERT(name(e) != clear_tag);	/* +++ history */
  if (name(e) == clear_tag)	/* uninitialised global */
  {
    long byte_size = (a.ashsize + 7) >> 3;
    bool temp = (l == 0 || (extname[0] == local_prefix[0] && extname[1] == local_prefix[1]));

    if (temp)
    {
      fprintf(as_file, "\t.lcomm\t");
    }
    else
    {
      fprintf(as_file, "\t.comm\t");
    }
    outlab(lab);
    fprintf(as_file, ",%ld\n", byte_size);

    return isa;
  }


  {

    /* align at least to word for speed of access */
    /* if size greater than 4 bytes, align on double boundry for speed */
    if (a.ashalign > 32 || a.ashsize > 32)
      fprintf(as_file, "\t.align\t3\n");
    else
      fprintf(as_file, "\t.align\t2\n");
    fprintf(as_file, "%s:\n", extname);

    evalone(e, 0);

    /* evalone does not always output .space to finish off up to size, so protect next one */
    set_align(a.ashalign);
  }

  return isa;
}


instore evaluated_const(exp e)
{
  instore isa;
  int lab;
  char *id;

  /* +++ to share consts */

  /* generate read only data */
  fprintf(as_file, "\t.csect\t[RO]\n");

  isa = evaluated(e, 0);

  lab = isa.b.base;

  id = ext_name(lab);

  /* generate .toc entry */
  fprintf(as_file, "\t.toc\n");
  fprintf(as_file, "T.%s:\n\t.tc\t%s[TC],%s\n", id, id, id);

  /* reset to default text segment */
  fprintf(as_file, "\t.csect\t[PR]\n");

  return isa;
}
long correct_shape(long n, int shpe)
{
  switch (shpe)
  {
   case scharhd:
    n = n<<24;
    n = n>>24;
    return n;
   case ucharhd:
    n = n & 0xff;
    return n;
   case swordhd:
    n = n<<16;
    n = n>>16;
    return n;
   case uwordhd:
    n = n & 0xffff;
    return n;
   case slonghd:
   case ulonghd:
    return n;
  }
  fail("Unknown shape in correct_shape");
  return 0;
}
