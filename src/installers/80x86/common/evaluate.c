/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/* 80x86/evaluate.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:51 $
$Revision: 1.1.1.1 $
$Log: evaluate.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.14  1997/04/21  08:07:04  pwe
 * init large arrays
 *
 * Revision 1.13  1997/03/20  16:23:38  pwe
 * dwarf2
 *
 * Revision 1.12  1996/02/01  09:34:36  pwe
 * PIC oddities for AVS
 *
 * Revision 1.11  1996/01/22  14:31:05  pwe
 * PIC const*const, contop top_tag & linux 64-bit ints
 *
 * Revision 1.10  1996/01/10  17:54:07  pwe
 * PIC constant array offsets
 *
 * Revision 1.9  1996/01/10  09:19:08  pwe
 * profile const & envoffset correction
 *
 * Revision 1.8  1996/01/05  16:25:30  pwe
 * env_size and env_offset within constant expressions
 *
 * Revision 1.7  1995/08/30  16:06:27  pwe
 * prepare exception trapping
 *
 * Revision 1.6  1995/08/04  08:29:15  pwe
 * 4.0 general procs implemented
 *
 * Revision 1.5  1995/03/10  17:45:13  pwe
 * collection of signed/unsigned small bitfields
 *
 * Revision 1.4  1995/02/20  13:37:19  pwe
 * correct alignment within n_of bitfield
 *
 * Revision 1.3  1995/02/20  12:19:21  pwe
 * alignment within n_of bitfield
 *
 * Revision 1.2  1995/01/30  12:56:07  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:30:23  jmf
 * Initial revision
 *
**********************************************************************/


#include "config.h"
#include "common_types.h"

#include "tags.h"
#include "basicread.h"
#include "expmacs.h"
#include "exp.h"
#include "shapemacs.h"
#include "flpt.h"
#include "coder.h"
#include "instr.h"
#include "out.h"
#include "check.h"
#include "codermacs.h"
#include "externs.h"
#include "install_fns.h"
#include "table_fns.h"
#include "flags.h"
#include "instr386.h"
#include "machine.h"
#include "localflags.h"
#include "assembler.h"
#include "messages_8.h"
#include "diag_fns.h"
#include "f64.h"

#include "evaluate.h"


/* PROCEDURES */


static void outsize
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  switch ((n+7)/8) {
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
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  switch (name(e)) {
    case  val_tag:
    case null_tag:
    case top_tag:
      {
	if (name(sh(e)) == offsethd && al2(sh(e)) >= 8) {
		return (no(e)>>3);
	}
        return (no (e));
      }
    case bitf_to_int_tag:
      {
	return evalexp (son (e));
      }
    case int_to_bitf_tag:
      {
	long  w = evalexp (son (e));
	if (shape_align(sh(e)) != 1) {
	  failer ("should be align 1");
	}
	if (shape_size(sh(e)) != 32) {
	  w &= ((1 << shape_size(sh(e))) - 1);
	}
	return w;
      }
    case not_tag:
      {
	return (~evalexp (son (e)));
      }
    case and_tag:
      {
	return (evalexp (son (e)) & evalexp (bro (son (e))));
      }
    case or_tag:
      {
	return (evalexp (son (e)) | evalexp (bro (son (e))));
      }
    case xor_tag:
      {
	return (evalexp (son (e)) ^ evalexp (bro (son (e))));
      }

    case shr_tag:
      {
	return (evalexp (son (e)) >> evalexp (bro (son (e))));
      }

    case shl_tag:
      {
	return (evalexp (son (e)) << evalexp (bro (son (e))));
      }

    case concatnof_tag:
      {
	long  wd = evalexp (son (e));
	return (wd | (evalexp (bro (son (e))) << shape_size(sh(son(e)))));
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
   	  return (no(son(e)) / 8);
	break;
      }
    case env_size_tag:
      {
	dec * et = brog(son(son(e)));
	if (et -> dec_u.dec_val.processed)
	  return (et -> dec_u.dec_val.index);
	break;
      }
    case offset_add_tag:
      {
    	return (evalexp(son(e))+evalexp(bro(son(e))));
      }
    case offset_max_tag:
      {
	long a = evalexp(son(e));
	long b = evalexp(bro(son(e)));
    	return (a > b ? a : b);
      }
    case offset_pad_tag:
      {
	return( rounder(evalexp(son(e)), shape_align(sh(e)) / 8));
      }
    case offset_mult_tag:
      {
    	return (evalexp(son(e))*evalexp(bro(son(e))));
      }
    case offset_div_tag:
    case offset_div_by_int_tag:
      {
    	return (evalexp(son(e))/evalexp(bro(son(e))));
      }
    case offset_subtract_tag:
      {
    	return (evalexp(son(e))-evalexp(bro(son(e))));
      }
    case offset_negate_tag:
      {
	return (- evalexp(son(e)));
      }
    case seq_tag:
      {
	if (name(son(son(e))) == prof_tag && last(son(son(e))))
	   return (evalexp(bro(son(e))));
	break;
      }
    case cont_tag:
      {
	if (PIC_code && name(son(e)) == name_tag && isglob(son(son(e)))
		&& son(son(son(e))) != nilexp
		&& !(brog(son(son(e))) -> dec_u.dec_val.dec_var))
	   return (evalexp(son(son(son(e)))));
	break;
      }
  }
  failer(BAD_VAL);
  return (0);
}


/* outputs a value */
static void evalval
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  int e_size = shape_size(sh(e));
  unsigned char  n = name (e);
  int ov;

  if (n == val_tag) {
    int k = (name(sh(e)) == offsethd && al2(sh(e)) != 1)
                  ? no(e)/8 : no(e);
    flt64 x;
    if (isbigval(e)) {
      x = flt_to_f64(k, is_signed(sh(e)), &ov);
      k = x.small;
    }
    switch (e_size) {
      case 8:
	outn ((long)k & 0xff);
	break;
      case 16:
	outn ((long)k & 0xffff);
	break;
      case 32:
	outn ((long)k);
	break;
      case 64:
	outn ((long)k);
	outs (", ");
	if (isbigval(e)) {
	  SET (x);
	  outn((long)x.big);
	} else
	if (is_signed(sh(e)) && k < 0)
	  outn((long)-1);
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
    outreal (e);
    return;
  };

  if (n == reff_tag && name(son(e)) == name_tag && isglob(son(son(e)))) {
    outopenbr();
    outs (brog (son (son (e))) -> dec_u.dec_val.dec_id);
    outs (" + ");
    outn ((long)(no (e) + no (son (e))) / 8);
    outclosebr();
    return;
  };

  if (n == name_tag) {
    if (no (e) != 0) {
      outopenbr();
      outs (brog (son (e)) -> dec_u.dec_val.dec_id);
      outs (" + ");
      outn ((long)no (e) / 8);
      outclosebr();
    }
    else
      outs (brog (son (e)) -> dec_u.dec_val.dec_id);
    return;
  };

  {
    int k = evalexp (e);
    switch (e_size) {
      case 8:
	outn ((long)k & 0xff);
	break;
      case 16:
	outn ((long)k & 0xffff);
	break;
      case 32:
	outn ((long)k);
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
    PROTO_N ( (n, isconst, al) )
    PROTO_T ( int n X int isconst X int al )
{
  if (n == 0)
     return;

  if (isconst) {
    while (al >= 32 && n >= 4) {
      outlong();
      outs ("0");
      outnl ();
      n -= 4;
    };
    while (n > 0) {
      outbyte();
      outs ("0");
      outnl ();
      --n;
    };
  }
  else {
    outs (".set .,.+");
    outn ((long)n);
    outnl ();
  };

  return;
}

/* does the work of outputting of constants recursively */
static void evalaux
    PROTO_N ( (e, isconst, al) )
    PROTO_T ( exp e X int isconst X int al )
{
  int e_size = shape_size(sh(e));
  unsigned char  n = name (e);

  if (n == compound_tag) {		/* output components in turn */
    int work = 0;
    exp offe;
    exp val;
    int bits_left = 0;
    int crt_off = 0;
    int off, offn, sz, nx, i;

    if (son(e) == nilexp)
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
	    outn ((long)work & 0xff);
            outnl();
            crt_off += 8;
            work = 0;
            bits_left = 0;
         };

       if (off < crt_off)
              failer(CPD_ORDER);
       if (off >= (crt_off + 8))
           {
              clear_out((off-crt_off)/8, isconst, al);
              crt_off = off & -8;
           };

       if (name(sh(val)) != bitfhd)
         {
           evalaux(val, isconst, (crt_off + al) & 56);
           crt_off += shape_size(sh(val));
         }
       else
         {
           offn = off - crt_off;
           sz = shape_size(sh(val));
           nx = (name(val)==int_to_bitf_tag) ? no(son(val)) : no(val);
           work += nx << offn;
           bits_left = offn+sz;
           if ((offn + sz) <= 32)
              { while ((offn+sz) >= 8)
                 {
	           outbyte();
	           outn ((long)work & 0xff);
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
	           outn ((long)work & 0xff);
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
	       outn ((long)work & 0xff);
               outnl();
               crt_off += 8;
            };
          clear_out((shape_size(sh(e)) - crt_off)/8, isconst,
			8);
          return;
        };
       offe = bro(val);
     };
  };

  if (n == string_tag) {
    char *s = nostr(e);
    int  goon;
    int  i,
          j;
    int char_size = (int)string_char_size(e);
    goon = shape_size(sh(e)) / char_size;
    for (i = 0; goon; i += 10) {
      switch (char_size)
       {
         case 8: outbyte(); break;
         case 16:outshort(); break;
         case 32:outlong(); break;
         case 64:outlong(); break;
       };

      for (j = i; goon && j < i + 10; ++j) {
        switch (props(e))
         {
           case 8: outn ((long) s[j]); break;
           case 16: outn ((long) ((short*)(void*)s)[j]); break;
		/* the pun to short* is correct: jmf */
           case 32: outn ((long) ((int*)(void*)s)[j]); break;
		/* the pun to int* is correct: jmf */
	   case 64: {
	     flt64 x;
	     int ov;
	     x = flt_to_f64(((int*)(void*)s)[j], 0, &ov);
	     outn((long)x.small); outs (", "); outn((long)x.big);
	   };
         };
	--goon;
	if (goon && j < i + 9)
	  outs (", ");
      };
      outnl ();
    };
    return;
  };

  if (n == res_tag) {
    int  nb;
    nb = shape_size(sh(son(e))) / 8;
    clear_out (nb, isconst, shape_align(sh(son(e))));
    return;
  };

  if (n == ncopies_tag) {
    int  m = no (e);
    int  sz, i;
    exp val = son(e);
    while ( name ( val ) == ncopies_tag ) {
	m *= no ( val ) ;
	val = son ( val ) ;
    }
    sz = shape_size(sh(val)) / 8;
    if ((name(val) == null_tag ||
	 name(val) == val_tag) && !isbigval(val) && no(val) == 0)
      clear_out (m * sz, isconst, shape_align(sh(val)));
    else {
      for (i = 0; i < m; i++)
	evalaux(val, isconst, al);
    }
    return;
  };

  if (n == nof_tag)
   {
     exp t = son(e);
     if (t == nilexp)
       return;
     while (1)
      {
        evalaux(t, isconst, al);
        if (last(t))
          return;
        t = bro(t);
        dot_align((shape_align(sh(t))<=8) ? 1 : shape_align(sh(t))/8);
      };
   };

  if (n == concatnof_tag) {
    evalaux (son (e), isconst, al);
    evalaux (bro (son (e)), isconst, (al +shape_size(son(e))) & 63);
    return;
  };

  if (n == clear_tag)
   {
     int sz = shape_size ( sh ( e ) ) / 8;
     clear_out (sz, isconst, al);
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
    PROTO_N ( (c, cname, s, isconst, global, diag_props) )
    PROTO_T ( exp c X int cname X char *s X int isconst X int global X diag_global * diag_props )
{
  int al = shape_align(sh(c));

  if (global && cname == -1) {
    outs (".globl ");
    outs (s);
    outnl ();
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
    DIAG_VAL_BEGIN (diag_props, global, cname, s);
#else
    diag_val_begin(diag_props, global, cname, s);
#endif

  if (cname == -1) {
    outs (s);
  }
  else {
    outs(local_prefix);
    outn ((long)cname);
  };

  outs (":");
  outnl();

  evalaux (c, isconst, al);

  if (global)
    eval_postlude(s, c);

  outnl ();

  if (diag_props) {
#ifdef NEWDWARF
    DIAG_VAL_END (diag_props);
#else
    diag_val_end(diag_props);
#endif
  }

  return;
}
