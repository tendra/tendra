/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * The main procedure defined here is evaluated which outputs assembly
 * for data. The parameters are an evaluated exp and an index
 * into the table of externals (or 0 meaning anonymous).
 */

#include <assert.h>
#include <ctype.h>

#include <local/expmacs.h>
#include <local/exptypes.h>
#include <local/fbase.h>
#include <local/szs_als.h>		/* for MAX_BF_SIZE */
#include <local/out.h>

#include <reader/basicread.h>

#include <construct/flags.h>
#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shapemacs.h>
#include <construct/flpttypes.h>
#include <construct/flpt.h>
#include <construct/f64.h>

#include "addrtypes.h"
#include "maxminmacs.h"
#include "translat.h"
#include "comment.h"
#include "inst_fmt.h"
#include "frames.h"
#include "procrec.h"
#include "eval.h"


#define proc_tag 118
#define is_zero( e ) is_comm( e )

/* various pieces of info for outputting data depending on shape */
static mm scmm = {127, -128, "\t.BYTE\t%ld\n"};
static mm uscmm = {255, 0, "\t.BYTE\t%ld\n"};
static mm shmm = {0x7fff, 0xffff8000, "\t.HALF\t%ld\n"};
static mm ushmm = {0xffff, 0, "\t.HALF\t%ld\n"};
static mm swmm = {0x7fffffff, 0x80000000, "\t.WORD\t%ld\n"};
static mm uswmm = {0xffffffff, 0, "\t.WORD\t%ld\n"};

/*
 * finds the data size from the range of an integer shape
 */
mm
maxmin(shape s)
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
    {
      return uswmm;
    }
  }

}

int
next_data_lab(void)
{
  static int n = 100;
  return ++n;
}

int
next_PIC_pcrel_lab(void)
{
  static int n = 100;
  return ++n;
}

/*
 * Output a unary representation of the number val. val should be
 * less than or equal to 31 as it represent the number of bits
 * in a bitfield which does not occupy a whole machine word.
 */
long
unary(int val)
{
   int loop;
   long result=0;
   assert (val <=31);
   for(loop=0;loop<val;++loop)
   {
      result <<=1;
      result |= 1;
   }
   return result;
}

/*
 * Output assembler representation of floating number
 */
static void outfloat(f)
flpt f;
{
#if ( FBASE == 10 )
  int i;
  int n;
  unsigned char *frac = (flptnos[f].mant);
  char *exppos;
  static char fltrepr[120];
  insection(data_section);

  for (n = MANT_SIZE - 1; n > 1 && frac[n] == 0; n--)
     /* BLOCKZ */ ;
  fltrepr[0] = (flptnos[f].sign < 0) ? '-' : '+';
  fltrepr[1] = frac[0] + '0';
  fltrepr[2] = '.';
  for (i = 1; i <= n; ++i)
  {
    fltrepr[i + 2] = frac[i] + '0';
  }
  exppos = &fltrepr[i + 2];
  if (flptnos[f].exp != 0)
  {
    sprintf(exppos, "e%ld", flptnos[f].exp);
  }
  else
  {
    exppos[0] = 0;
  }
  outs(fltrepr);
#else
  fail ( "Illegal floating point constant" ) ;
#endif
}

/*
 * CONVERT A REAL VALUE TO A BITPATTERN
 *
 * This routine converts the real constant e into an array of longs giving the
 * bitpattern corresponding to this constant. Although care has been taken,
 * this may not work properly on all machines (although it should for all
 * IEEE machines).
 * It returns NULL if it cannot convert the number sufficiently accurately.
 */
long *
realrep(exp e)
{
    int i, ex ;
    char bits [128] ;
    static long longs [4] ;
    int exp_bits, mant_bits ;
    long sz = shape_size ( sh ( e ) ) ;

#if ( FBASE == 10 )
    return NULL;
#else

    /* Find size of exponent and mantissa */
    if ( sz == 32 ) {
	exp_bits = 8 ;
	mant_bits = 23 ;
    } else if ( sz == 64 ) {
	exp_bits = 11 ;
	mant_bits = 52 ;
    } else {
	exp_bits = 15 ;
	mant_bits = 96 /* or 112? */ ;
    }

    if ( name ( e ) == real_tag ) {
	int j, k = -1 ;
	flt *f = flptnos + no ( e ) ;

	/* Deal with 0 */
	if ( f->sign == 0 ) {
	    for ( i = 0 ; i < sz / 32 ; i++ ) longs [i] = 0 ;
	    return longs;
	}

	/* Fill in sign */
	bits [0] = ( f->sign < 0 ? 1 : 0 ) ;

	/* Work out exponent */
	ex = FBITS * ( f->exp ) + ( FBITS - 1 ) ;

	/* Fill in mantissa */
	for ( i = 0 ; i < MANT_SIZE ; i++ ) {
	    for ( j = FBITS - 1 ; j >= 0 ; j-- ) {
		if ( ( f->mant [i] ) & ( 1 << j ) ) {
		    if ( k >= 0 ) {
			if ( k < sz ) bits [k] = 1 ;
			k++ ;
		    } else {
			/* Ignore first 1 */
			k = exp_bits + 1 ;
		    }
		} else {
		    if ( k >= 0 ) {
			if ( k < sz ) bits [k] = 0 ;
			k++ ;
		    } else {
			/* Step over initial zeros */
			ex-- ;
		    }
		}
	    }
	}

    } else {
	fail ( "Illegal floating-point constant" ) ;
	return NULL;
    }

    /* Fill in exponent */
    ex += ( 1 << ( exp_bits - 1 ) ) - 1 ;
    if ( ex <= 0 || ex >= ( 1 << exp_bits ) - 1 ) {
	fail ( "Floating point constant out of range" ) ;
    }
    for ( i = 0 ; i < exp_bits ; i++ ) {
	int j = exp_bits - i ;
	bits [j] = ( ( ex & ( 1 << i ) ) ? 1 : 0 ) ;
    }

    /* Convert bits to longs */
    for ( i = 0 ; i < sz / 32 ; i++ ) {
	int j ;
	long b0 = 0, b1 = 0, b2 = 0, b3 = 0 ;
	for ( j = 0 ; j < 8 ; j++ ) b0 = 2 * b0 + bits [ 32 * i + j ] ;
	for ( j = 8 ; j < 16 ; j++ ) b1 = 2 * b1 + bits [ 32 * i + j ] ;
	for ( j = 16 ; j < 24 ; j++ ) b2 = 2 * b2 + bits [ 32 * i + j ] ;
	for ( j = 24 ; j < 32 ; j++ ) b3 = 2 * b3 + bits [ 32 * i + j ] ;
	switch (endian) {
	case ENDIAN_LITTLE:
		longs [i] = b0 + ( b1 << 8 ) + ( b2 << 16 ) + ( b3 << 24 ) ;
		break;
	case ENDIAN_BIG:
		longs [i] = ( b0 << 24 ) + ( b1 << 16 ) + ( b2 << 8 ) + b3 ;
		break;
	}
    }
    return longs;
#endif
}

long
evalexp(exp e)
{
  switch (name(e))
  {
  case top_tag:
     return 0;
  case val_tag: case null_tag:
  {
     if (name(sh(e)) == offsethd && al2(sh(e)) >= 8) 
     {
	return no(e)>>3;
     }
     else
	return no(e);
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
      if (a.ashalign != 1 && !(name(sh(e)) == cpdhd && a.ashalign == 32))
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
      return evalexp(son(e));
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

      FULLCOMMENT1("evalexp() shr_tag: sgned=%d", sgned);
      if (sgned)
	return ((long) evalexp(son(e))) >> evalexp(bro(son(e)));
      else
	return ((unsigned long) evalexp(son(e))) >> evalexp(bro(son(e)));
    }

  case shl_tag:
    {
      return evalexp(son(e)) << evalexp(bro(son(e)));
    }

  case concatnof_tag:
    {
      unsigned long w_lhs = evalexp(son(e));
      unsigned long w_rhs = evalexp(bro(son(e)));
      ash ash_lhs, ash_rhs ;
      ash_lhs = ashof(sh(son(e)));
      ash_rhs = ashof(sh(bro(son(e))));

      assert(ash_lhs.ashalign == 1 && ash_lhs.ashsize <= 32);
      assert(ash_rhs.ashalign == 1 && ash_rhs.ashsize <= 32);
      assert(ash_lhs.ashsize + ash_rhs.ashsize <= 32);

      FULLCOMMENT4("evalexp() concatnof_tag: lhs,rhs=%#x,%#x ash(rhs)=%d,%d",
		   w_lhs, w_rhs, ash_rhs.ashalign, ash_rhs.ashsize);

      if (ash_rhs.ashsize == 32)
      {
	/* avoid illegal shift by 32 */
	assert(w_lhs == 0);
	return w_rhs;
      }
      return (w_lhs << ash_rhs.ashsize) | w_rhs;
    }

  case env_offset_tag:
  case general_env_offset_tag: 
  {
     return frame_offset(son(e));
  }
  case env_size_tag:
  {
     exp tg = son(son(e));
     procrec * pr = &procrecs[no(son(tg))];
     return (pr->frame_sz+0) >> 3;
  }

   case offset_add_tag:
   {
    	return evalexp(son(e))+evalexp(bro(son(e)));
   }
   case offset_max_tag:
   {
    	return MAX_OF(evalexp(son(e)),evalexp(bro(son(e))));
   }   
   case offset_pad_tag:
   {
	return rounder(evalexp(son(e)), shape_align(sh(e)));
   }
   case offset_mult_tag:
   {
    	return evalexp(son(e))*evalexp(bro(son(e)));
   }
   case offset_div_tag:case offset_div_by_int_tag:
   {
    	return evalexp(son(e))/evalexp(bro(son(e)));
   }
   case offset_subtract_tag:
   {
    	return evalexp(son(e))-evalexp(bro(son(e)));
   }
   case offset_negate_tag: 
   {
	return -evalexp(son(e));
   }     

  case clear_tag:
    {
      ash a;

      a = ashof(sh(e));

      FULLCOMMENT2("evalexp() clear_tag: ash=%d,%d", a.ashalign, a.ashsize);

      return 0;
    }


  default:
    fail("tag not in evalexp");
    return 0;
  }
  /* NOTREACHED */
}

void
oneval(int val, int al, int rep)
{
    assert ( rep == 1 ) ;     
    outs( (al<9 ? "\t.BYTE\t" : ( al<17 ? "\t.HALF\t" : "\t.WORD\t")) );
    outn( val);
    outnl();
    return ;
}

/*
 * Output as ascii for the human reader (48 bytes to the line).
 */
static void
outascii(char * str, int strsize)
{
    while ( strsize > 0 ) {
	int i ;
	outs("\t.STRING\t\"");
	for ( i = 0 ; strsize > 0 && i < 48 ; i++ ) {
	    unsigned char c = ( ( unsigned char ) *str ) ;
	    switch ( c ) {
		case '"' : {
		    outs( "\\\"") ;
		    break ;
		}
		case '\\' : {
		    outs( "\\\\" ) ;
		    break ;
		}
		case 7 : {
		    outs( "\\x07" ) ;
		    break ;
		}
		case '\b' : {
		    outs( "\\x08" ) ;
		    break ;
		}
		case '\f' : {
		    outs( "\\x0c" ) ;
		    break ;
		}
		case '\n' : {
		    outs( "\\x0a" ) ;
		    break ;
		}	
		case '\r' : {
		    outs( "\\x0d" ) ;
		    break ;
		}
		case '\t' : {
		    outs( "\\x09" ) ;
		    break ;
		}
		case 11 : {
		    outs( "\\x0b" ) ;
		    break ;
		}
		default :
		{
		    if (isprint(c))
		       outc(c);
		    else 
			/* output as a hexadecimal  */
		    {
		       if (c<16)
			   fprintf(outf,"\\x0%x", c) ;
		       else
			   fprintf(outf,"\\x%x", c) ;
		    }
  	            break ;
		}
	    }
	    str++ ;
	    strsize-- ;
	}
	outs("\"\n");
    }
    return ;
  }


struct concbittypet
{
  int bitposn;
  int value_size;
  unsigned long value;
};
typedef struct concbittypet concbittype;


static concbittype
emptyconcbit(int bitposn)
{
  concbittype start;

  start.bitposn = bitposn;
  start.value_size = 0;
  start.value = 0;

  return start;
}


static void
outconcbit(concbittype c)
{
  unsigned long w = c.value;
  int bytes = (c.value_size + 7) / 8;
  int i;

  insection(data_section);

  comment2("outconcbit: bits=%d w=%#lx", c.value_size, w);

  if (c.value_size == 0)
    return;			/* avoid .BYTE with no data */

  assert(c.value_size <= 32);

  /* to left end of word */
  if (c.value_size != 32)
    w = w << (32 - c.value_size);

  /* HPPA assembler only permits .WORD for 32-bit aligned values */

  /* output enough bytes */
  outs("\t.BYTE\t") ;
  for (i = 0; i < bytes; i++)
  {
    if (i != 0)
       outc(',') ;
    fprintf(outf,"%#lx", ( w >> 24 ) & 255 ) ;
    w = w << 8;
  }
  outnl();
  assert(w == 0);
}

/*
 * Add a value to a bit pattern
 */
static concbittype
addconcbitaux(unsigned long w, int sz, concbittype before)
{
   int wordpos;  /* bit position in word */

   if ( before.value_size == 32 || (before.value_size != 0 && (before.bitposn & 31) == 0) )
   {
      assert((before.bitposn & 31) == 0);
      wordpos = 32;
   }
   else
   {
      wordpos = (before.bitposn & 31);
   }
   assert(sz > 0);
   assert(sz <= 32);
   assert(before.value_size <= 32);
   assert(wordpos == 0 || before.value_size <= wordpos);
   if ( (sz == 0 && (wordpos != 0 || before.value_size != 0)) ||
	((wordpos+sz) > 32) )
   {
/*      int pad_bits = 32 - wordpos;    gcc complains*/
      assert ( wordpos == 32 ); /* should be aligned automatically */
      outconcbit(before);
      /* clear before, as it has been output */
      before.value_size = 0;
      before.value = 0;
      /* should be at word boundary */
      assert((before.bitposn & 31) == 0);
   }

   if (sz == 0)
      return before;

   /* add to before */
   if (sz == 32)
      before.value = w;
   else
   {
	switch (endian) {
	case ENDIAN_LITTLE:
      		before.value = before.value | ( w << before.value_size ) ;
		break;
	case ENDIAN_BIG:
      		before.value = ( before.value << sz ) | (w & unary(sz));
		break;
	}
   }
   before.bitposn += sz;
   before.value_size += sz;
   assert(before.value_size <= 32);
   return before;
}


static concbittype
evalconcbitaux(exp e, concbittype before)
{
  switch (name(e))
  {
    case concatnof_tag:
    {
      concbittype lhs, rhs ;
      lhs = evalconcbitaux(son(e), before);
      rhs = evalconcbitaux(bro(son(e)), lhs);
      return rhs;
    }

  default:
    {
      assert(shape_align(sh(e)) == 1);

      return addconcbitaux(evalexp(e), shape_size(sh(e)), before);
    }
  }
}


static void
evalconcbit(exp e, int bitposn)
{
  concbittype start ;
  start = emptyconcbit(bitposn);
  outconcbit(evalconcbitaux(e, start));
}

/*
 * Determine whether an exp is definitely zero valued. Zero-valued initialisers
 * can be put in the bss section. Does not exhaust all possibilities;
 * some zero valued expressions may have "is_zero(e) == 0".
 */
#if 0
bool
is_zero(exp e)
{
  if (e == nilexp)
    return 1;

  switch (name(e))
  {
    /* +++ real values always explicitly initialised, which is not necessary */
  case null_tag:
    return 1;
  case val_tag:
    return no(e) == 0 ? 1 : 0;
  case ncopies_tag:
  case int_to_bitf_tag:
    return is_zero(son(e));
  case compound_tag:
    {
      /* (compound_tag <offset> <initialiser> ... ) */
      e = bro(son(e));
      while (1)
      {
	if (is_zero(e) == 0)
	  return 0;		/* found non-zero */

	if (last(e))
	  return 1;		/* all done, all zero */

	e = bro(bro(e));
      }
      /*NOTREACHED*/
    }
 case real_tag:
    {
      /* correct because bit representation of real zero is all zero bits */
      flt f ;
      f = flptnos[no(e)];
      if (f.exp == 0)
      {
	int i;
	for (i = 0; i < MANT_SIZE; i++)
	    if (f.mant[i] != 0)
		return 0;	/* non-zero */
	
	return 1;		/* all zero */
      }
      return 0;
    }
  default:
      return 0;
  }
}
#endif

void
set_align(int al)
{
    assert ( al >= 8 && al <= 64 ) ;
    if ( al > 8 ) {
       outs("\t.ALIGN\t");
       outn(al/8);
       outnl();
    }
    return ;
}

/*
 * This procedure outputs all expressions.
 */
void
evalone(exp e, int bitposn)
{
  ash a;
/*  long al = ( long ) shape_align ( sh ( e ) ) ; gcc complains */
  long sz = ( long ) shape_size ( sh ( e ) ) ;

  insection(data_section);

  a = ashof(sh(e));

  comment4("evalone: name(e)=%d, bitposn=%d, ash=%d,%d", name(e), bitposn, a.ashsize, a.ashalign);

  set_align(a.ashalign);

  /* align bitposn */
  if (a.ashalign != 0)
    bitposn = (bitposn / a.ashalign) * a.ashalign;

  /* generate data initialiser for e */
  switch (name(e))
  {
    case string_tag:
      {
	  long char_size=props(e);
	  long strsize=shape_size(sh(e))/char_size;
	  char *st=nostr(e);
	  int i,j;
    
	  if (char_size==8)
	  {
	    outascii(st,strsize);
	    return;
	  }

	  if (strsize>0)
	     set_align(char_size);
	  
	  for (j=0; j<strsize;)
	  {
	     outs( char_size==8 ? "\t.BYTE\t" :
				  ( char_size==16 ? "\t.HALF\t" : "\t.WORD\t") );
	  /* output chars in batches */
	  for (i = j; i < strsize && i-j < 8; i++)
	  {
	    if (i != j)
	       outc(',');
/*	    switch (ptno(e)) */
	    switch ( char_size )
	    {
	  case 8:
	      fprintf(outf,"0x%x", st[i]);
	      break;
	  case 16:
	      fprintf(outf,"0x%x", ((short *) st)[i]);
	      break;
	  case 32:
	      fprintf(outf,"0x%x", ((int *) st)[i]);
	    break;
	    }
	  }/*for i*/
	  outnl();
	  j = i;
	}/*for j*/
      return;
    }

    case real_tag :
      if (use_long_double) {
	    /* Floating point constant */
	  flt *f = flptnos + no ( e ) ;
	  r2l v;
	  
	  if ( sz == 32 ) {
	    v = real2longs_IEEE(f,0);
    		
	    outs ( "\t.WORD\t" ) ;
	    outn ( v.i1 ) ;
	  } else if ( sz == 64 ) {
	    v = real2longs_IEEE(f,1);
	    
	    outs ( "\t.WORD\t" ) ;
	    outn ( v.i2 ) ;
	    outc ( ',' ) ;
	    outn ( v.i1 ) ;
	  } else {
	    v = real2longs_IEEE(f,2);
	    outs ( "\t.WORD\t" ) ;
	    outn ( v.i4 ) ;
	    outc ( ',' ) ;
	    outn ( v.i3 ) ;
	    outc ( ',' ) ;
	    outn ( v.i2 ) ;
	    outc ( ',' ) ;
	    outn ( v.i1 ) ;
	  }
	  outnl () ;
    } else {
	long sz = a.ashsize ;
	long *p = realrep ( e ) ;
	if ( p )
	{
	    outs("\t.WORD\t");
	    outn(p[0]);
	    if ( sz > 32 )
	    {
		outc(',') ;
		outn(p[1]);
	    }
	    outnl();
	}
	else
	{
	    if (sz==32)
	       outs( sz==32 ? "\t.FLOAT\t0r" : "\t.DOUBLE\t0r");
	    outfloat(no(e));
	    outnl();
	}
      }
    return ;

    case null_tag: case top_tag:
    no(e) = 0;
    /* FALLTHROUGH */
  case val_tag:
    {
       if ( shape_size(sh(e))>32 ) 
       {
	  flt64 t;
	  int ov;
	  if (isbigval(e)) 
	  {
	     t = flt_to_f64(no(e),0,&ov);
	  }
	  else
	  {
	     t.big = (is_signed(sh(e)) && no(e)<0)?-1:0;
	     t.small = no(e);
	  }
	  oneval(t.big,32,1);
	  oneval(t.small,32,1);
	  return;
       }
       if ( a.ashalign==1 )
	  evalconcbit(e, bitposn);
       else
	  oneval(evalexp(e),a.ashalign,1);
       return;
    }

    case name_tag : {
	dec *globdec = brog(son(e)) ;	/* must be global name */
	char *nm = globdec->dec_u.dec_val.dec_id ;

	assert(isglob(son(e)));

	if ( son(globdec->dec_u.dec_val.dec_exp)!=nilexp &&
	     ( name(son(globdec->dec_u.dec_val.dec_exp))==proc_tag ||
	       name(son(globdec->dec_u.dec_val.dec_exp))==general_proc_tag ) )
	{
	   /* It's a plabel */
	   outs( "\t.WORD\tP%" ) ;
	}
	else
	   outs( "\t.WORD\t" ) ;
	outs(nm) ;
	if ( no ( e ) ) {
	    outc('+') ;
	    outn(no(e)/8);
	}
	outnl();
	return ;
    }

  case compound_tag:
  {
      /* Compound values */
      exp off = son(e);
      exp tup = bro(off);
      ash tupa;
      concbittype left;
      long last_offset = 0;
      long last_align = 0;
      tupa = ashof(sh(tup));
      left = emptyconcbit(bitposn);

      /* output elements of aggregate recursively */
      while (1)
      {
	 int gap = no(off) - left.bitposn;

 	 /* check that component's alignment matches offset in struct */
/* XXX: what declares ta?
	 assert((no(off)/ta)*ta <= no(off));
*/
	 /* and is no greater than struct's alignment */
/* XXX: what declares maxalign?
	 assert(tupa.ashalign <= maxalign);
*/

	 if ( shape_size(sh(tup)) == 0 )
	 {
	    if (last(tup)) 
	       return;
	    else
	    {
	       off = bro(bro(off));
	       assert(!last(off));
	       tup = bro(off);
	       tupa = ashof(sh(tup));
	       continue;
	    }
	 }

 	 if (no(off) < last_offset)
	 {
	    fail( "Compound components badly ordered" ) ;
	 }
	 if (last_align <= 1 || tupa.ashalign <= 1 || gap >= tupa.ashalign)
	 {
	    /* get gap down */
	    while (gap > 0)
	    {
	       left = addconcbitaux(0,1,left);
	       gap--;
	    }
	 }
 	 else
	 {
	    /* alignment will handle gap */
	    left.bitposn = (int) rounder(left.bitposn,tupa.ashalign);
	 }
 	 last_offset = no(off);
	 last_align = tupa.ashalign;
	 assert(left.bitposn - bitposn == no(off));
 	 if (tupa.ashalign == 1)
	 {
	    /* collect bitfields */
 	    left = evalconcbitaux(tup,left);
	 }
	 else
	 {
	    /* output final bits from any previous field */
	    outconcbit(left);
	    left = emptyconcbit(left.bitposn);
 	    evalone(tup,left.bitposn);
	    left.bitposn += tupa.ashsize;
	 }
 	 if (last(tup))
	 {
	    /* output final bits from any previous field */
	    long databits = no(off) + tupa.ashsize;
	    long trailing_bytes = (a.ashsize-databits) / 8;
	    outconcbit(left);
	    assert(a.ashsize >= databits);

	    /* pad out trailing unitialised space, eg union */
	    if (a.ashsize > databits && trailing_bytes > 0)
	    {
	       outs( "\t.BLOCKZ\t" ) ;
	       outn(trailing_bytes);
	       outnl();
	    }
 	    return;
	 }
 	 off = bro(bro(off));
	 assert(!last(off));
	 tup = bro(off);
	 tupa = ashof(sh(tup));
      }
      /*  NOT REACHED  */
    }

  case nof_tag:
    {
      exp s = son(e);
      set_align(a.ashalign);
      for (;;)
      {
	evalone(s, bitposn);
	if (last(s))
	  return;
	s = bro(s);
      }
    }

  case ncopies_tag:
   {
      int n = no(e);
      ash copya;
      int bitsize;
      int i;

      while (name(son(e)) == ncopies_tag)
      {
	e = son(e);
	n *= no(e);
      }

      e = son(e);

      copya = ashof(sh(e));
      if (copya.ashalign != 0)
	bitsize = (copya.ashsize / copya.ashalign) * copya.ashalign;
      else
	bitsize = 0;		/* probably never happen! */

      for (i = 0; i < n; i++)
      {
	evalone(e, bitposn);
      }
      return;
    }

  case concatnof_tag:
    {
      comment2("concatnof_tag: ashalign=%d, ashsize=%d", a.ashalign, a.ashsize);

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
	  bitposn = (bitposn / a.ashalign) * a.ashalign;
	evalone(bro(son(e)), bitposn);
      }
      return;
    }

    case clear_tag : {
	if ( a.ashalign == 1 ) {
	    /* allow for bitfields */
	    evalconcbit ( e, bitposn ) ;
	    return ;
	}
	outs( "\t.BLOCKZ\t" ) ;
	outn((a.ashsize+7)>>3);
	outnl();
	return ;
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
    {
	outs( "\t.WORD\t" ) ;
	outn(evalexp(e));
	outnl();
	return ;
    }
   case env_size_tag:
    {
	exp tg = son(son(e));
	procrec * pr = &procrecs[no(son(tg))];
	outs( "\t.WORD\t" ) ;
	outn((pr->frame_sz+0) >> 3);
	outnl();
	return ;
    }

   case offset_add_tag:
   {
	outs( "\t.WORD\t" ) ;
    	outn(evalexp(son(e))+evalexp(bro(son(e))));
	outnl();
	return ;
   }
   case offset_max_tag:
   {
	outs( "\t.WORD\t" ) ;
    	outn(MAX_OF(evalexp(son(e)),evalexp(bro(son(e)))));
	outnl();
	return ;
   }   
   case offset_pad_tag:
   {
	outs( "\t.WORD\t" ) ;
	outn( rounder(evalexp(son(e)), shape_align(sh(e))));
	outnl();
	return ;
   }
   case offset_mult_tag:
   {
	outs( "\t.WORD\t" ) ;
    	outn(evalexp(son(e))*evalexp(bro(son(e))));
	outnl();
	return ;
   }
   case offset_div_tag:case offset_div_by_int_tag:
   {
	outs( "\t.WORD\t" ) ;
    	outn(evalexp(son(e))/evalexp(bro(son(e))));
	outnl();
	return ;
   }
   case offset_subtract_tag:
   {
	outs( "\t.WORD\t" ) ;
    	outn(evalexp(son(e))-evalexp(bro(son(e))));
	outnl();
	return ;
   }
   case offset_negate_tag: 
   {
	outs( "\t.WORD\t" ) ;
	outn(-evalexp(son(e)));
	outnl();
	return ;
   }     

  case chvar_tag : {
	    if ( shape_size ( sh ( e ) ) == shape_size ( sh ( son ( e ) ) ) ) {
		sh ( son ( e ) ) = sh ( e ) ;
		evalone ( son ( e ), bitposn ) ;
	    } else {
		fail ( "Illegal chvar constant" ) ;
	    }
	    return ;
	}

    default: 
       fail("tag not in evaluated");

  }				/* end switch */
}

/*
 * Outputs data initialisers for the evaluated exp.
 * The result is the instore "address" of the constant.
 * A negative l implies that this is the initialisation of a global variable.
 */
instore
evaluated(exp e, long l)
{
  int lab = (l == 0) ? next_data_lab() : (l < 0) ? l : -l;
  int lab0 = lab;
  instore isa;
  exp z = e;
  ash a ;
  bool extnamed = (l == 0) ? 0 : main_globals[-lab - 1]->dec_u.dec_val.extnamed;
  a = ashof(sh(e));

  FULLCOMMENT2("evaluated: %s %ld", (int)TAG_NAME(name(e)), l);

  isa.adval = 0;
  isa.b.offset = 0;
  isa.b.base = lab0;

  if (is_zero(e))
  {
    int byte_size = (a.ashsize + 7) >> 3;
    int align = ((a.ashalign > 32 || a.ashsize > 32) ? 8 : 4);
    if (!extnamed)
    {
       /* uninitialised global */
       if (byte_size>8)
	  insection(bss_section);
       else
	  insection(shortbss_section);
       outs("\t.ALIGN\t");
       outn(align);
       outnl();
       outs( ext_name(lab) ) ;
       outs("\t.BLOCK\t");
       outn(byte_size);
       outnl();
    }
    else
    {
      /* align at least to word for speed of access */
      /* if size greater than 4 bytes, align on double boundry for speed */
      if (a.ashalign > 32 || a.ashsize > 32)
	  set_align(64);
      else
	  set_align(32);

      if (byte_size>8)
	 insection(bss_section);
      else
	 insection(shortbss_section);
      outs( ext_name(lab) ) ;
      outs("\t.COMM\t");
      outn(byte_size);
      outnl();
    }
  }
  else
  {
     insection(data_section);
     /* align at least to word for speed of access */
     /* if size greater than 4 bytes, align on double boundry for speed */
     if (a.ashalign > 32 || a.ashsize > 32)
	set_align(64);
     else
	set_align(32);
     outs( ext_name(lab) ) ;
     outnl();
     evalone(z, 0);
     /* evalone does not output .BLOCKZ to finish off up to size, so protect next one */
     if (a.ashalign > 32)
	set_align(64);
  }
  return isa;
}

