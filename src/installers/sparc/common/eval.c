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




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/eval.c,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: eval.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.15  1997/10/23  09:32:48  pwe
 * prep extra_diags
 *
 * Revision 1.14  1997/10/10  18:32:13  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.13  1997/04/18  11:47:50  pwe
 * init large arrays
 *
 * Revision 1.12  1997/04/17  11:59:35  pwe
 * dwarf2 support
 *
 * Revision 1.11  1997/02/18  11:47:42  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.10  1996/12/19  12:59:53  pwe
 * SUNOS link from library with dynamic init
 *
 * Revision 1.9  1996/03/20  16:14:04  john
 * Reformatting
 *
 * Revision 1.8  1996/01/24  18:10:51  john
 * Added several constructs to eval
 *
 * Revision 1.7  1995/12/15  10:12:05  john
 * portability change
 *
 * Revision 1.6  1995/10/04  09:00:24  john
 * Added 64 bit constants
 *
 * Revision 1.5  1995/08/24  16:38:49  john
 * Changed to string_tag
 *
 * Revision 1.4  1995/07/14  16:30:21  john
 * Reformatting
 *
 * Revision 1.3  1995/05/26  12:57:27  john
 * Changes for new spec (3.1)
 *
 * Revision 1.2  1995/04/20  08:04:57  john
 * Fix to bitfields
 *
 * Revision 1.1.1.1  1995/03/13  10:18:32  john
 * Entered into CVS
 *
 * Revision 1.5  1995/01/06  13:54:51  john
 * Changed name of variable, because of clash with identical type name.
 *
 * Revision 1.4  1994/12/01  13:28:00  djch
 * Globals can be inited to env_offsets. Call boff_env_offset to get this
 *
 * Revision 1.3  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.2  1994/05/25  14:16:36  djch
 * removed realrep, now use jmf's real2longs_IEEE
 *
 * Revision 1.1  1994/05/03  14:49:34  djch
 * Initial revision
 *
 * Revision 1.9  93/11/19  16:28:46  16:28:46  ra (Robert Andrews)
 * Added chvar_tag case.
 * 
 * Revision 1.8  93/09/27  14:42:49  14:42:49  ra (Robert Andrews)
 * Extend floating-point constants to deal with long doubles.  Add
 * know_size flag (see translat.c).
 * 
 * Revision 1.7  93/08/27  11:23:50  11:23:50  ra (Robert Andrews)
 * A number of lint-like changes.
 * 
 * Revision 1.6  93/08/18  11:10:06  11:10:06  ra (Robert Andrews)
 * Added minptr case to constant evaluation routine (Grenoble bug) to
 * allow constants of the form external - external.
 * 
 * Revision 1.5  93/07/12  15:12:25  15:12:25  ra (Robert Andrews)
 * Minor reformatting.
 * 
 * Revision 1.4  93/07/09  16:12:31  16:12:31  ra (Robert Andrews)
 * Reformatted.  Added support for little-endian machines (I've heard that
 * a little-endian SPARC is in the pipeline).  Changed is_zero to use
 * is_comm.
 * 
 * Revision 1.3  93/07/05  18:18:47  18:18:47  ra (Robert Andrews)
 * Made distinction between the System V assembler and the System V ABI.
 * 
 * Revision 1.2  93/06/29  14:24:07  14:24:07  ra (Robert Andrews)
 * Changed method of representing characters in strings.
 * 
 * Revision 1.1  93/06/24  14:58:09  14:58:09  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE

/*
    This file contains routines for outputting constant initialisations.
*/

#include "config.h"
#include <ctype.h>
#include "addrtypes.h"
#include "common_types.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"
#include "exptypes.h"
#include "maxminmacs.h"
#include "shapemacs.h"
#include "flpttypes.h"
#include "flpt.h"
#include "fbase.h"
#include "translat.h"
#include "comment.h"
#include "myassert.h"
#include "inst_fmt.h"
#include "szs_als.h"
#include "out.h"
#include "locate.h"
#include "regmacs.h"
#include "f64.h"
#include "procrec.h"
#include "bitsmacs.h"
#include "installglob.h"
#include "eval.h"
#ifdef NEWDWARF
#include "dw2_config.h"
#endif
/*
    INFORMATION FOR OUTPUTTING DATA

    The values are maximum, minimum, output directive.
*/

static mm scmm = { 127, -128, "\t.byte\t%ld\n" } ;
static mm uscmm = { 255, 0, "\t.byte\t%ld\n" } ;
static mm shmm = { 0x7fff, 0xffff8000, "\t.half\t%ld\n" } ;
static mm ushmm = { 0xffff, 0, "\t.half\t%ld\n" } ;
static mm swmm = { 0x7fffffff, 0x80000000, "\t.word\t%ld\n" } ;
static mm uswmm = { 0xffffffff, 0, "\t.word\t%ld\n" } ;

#define max(X,Y) ((X>Y)?X:Y)

/*
    FIND THE OUTPUT DATA CORRESPONDING TO A SHAPE
*/

mm maxmin 
    PROTO_N ( ( s ) )
    PROTO_T ( shape s ){
  switch ( name ( s ) ) {
    case scharhd : return ( scmm ) ;
    case ucharhd : return ( uscmm ) ;
    case swordhd : return ( shmm ) ;
    case uwordhd : return ( ushmm ) ;
    case slonghd : return ( swmm ) ;
    case ulonghd : return ( uswmm ) ;
  }
  return ( uswmm ) ;
}


/*
    FIND THE NEXT DATA LABEL
*/

int next_data_lab 
    PROTO_Z (){
  static int data_lab = 100 ;
  return ( ++data_lab ) ;
}


/*
    OUTPUT A LABEL
*/

void outlab 
    PROTO_N ( ( ll ) )
    PROTO_T ( int ll ){
  /* no preference for section here */
  outs ( ext_name ( ll ) ) ;
  return ;
}


/*
  OUTPUT A FLOATING POINT CONSTANT

  This routine should only be called if FBASE is 10.
*/

#if 0
static void outfloat 
    PROTO_N ( ( f, ro ) )
    PROTO_T ( flpt f X bool ro ){
#if ( FBASE == 10 )
  int i, n ;
  unsigned char *frac = flptnos [f].mant ;
  char *exppos ;
  char fltrepr [120] ;
  if (ro)
    insection ( rodata_section ) ;
  else
    insection ( data_section ) ;
  for ( n = MANT_SIZE - 1 ; n > 1 && frac [n] == 0 ; n-- ) /* SKIP */ ;
  fltrepr [0] = ( ( flptnos [f].sign < 0 ) ? '-' : '+' ) ;
  fltrepr [1] = frac [0] + '0' ;
  fltrepr [2] = '.' ;
  for ( i = 1 ; i <= n ; ++i ) fltrepr [ i + 2 ] = frac [i] + '0' ;
  exppos = &fltrepr [ i + 2 ] ;
  if ( flptnos [f].exp != 0 ) {
    sprintf ( exppos, "e%ld", flptnos [f].exp ) ;
  } 
  else {
    exppos [0] = 0 ;
  }
  outs ( fltrepr ) ;
#else
  fail ( "Illegal floating point constant" ) ;
#endif
  return ;
}
#endif



/*
  FIND THE VALUE OF AN INTEGER CONSTANT EXPRESSION
*/
long evalexp 
    PROTO_N ( ( e ) )
    PROTO_T ( exp e ){
  switch ( name ( e ) ) {
    case val_tag : {
      if(name(sh(e)) == offsethd && al2(sh(e))>=8) {
	return no(e)>>3;
      }
      else {
	return ( no ( e ) ) ;
      }
    }	
    case general_env_offset_tag :
    case env_offset_tag : {
      exp id = son(e);	/* as per tags.h, son is ident, not name */
    
      assert (name(id) == ident_tag);
    
      return boff_env_offset(id);
    }
    case env_size_tag : {
      exp tg = son(son(e));
      procrec *pr = &procrecs[no(son(tg))];
      bool leaf = (long)((pr->needsproc.prps & anyproccall) == 0);
      int arg_space;
      if(leaf) {
	arg_space = 16*32;
      }
      else {
	arg_space = ((max(pr->needsproc.maxargs,6*32)+((16+1)*32))+63)&~63;
      }
      return ( ((pr->spacereqproc.stack+63)&~63) + 
	       pr->needsproc.callee_size +arg_space)>>3;
    }
        
    case offset_add_tag : {
      return (evalexp(son(e)) + evalexp(bro(son(e))));
    }
    case offset_max_tag : {
      return (max(evalexp(son(e)),evalexp(bro(son(e)))));
    }
    case offset_pad_tag : {
      return (rounder(evalexp(son(e)),shape_align(sh(e))));
    }
    case offset_mult_tag : {
      return (evalexp(son(e))*evalexp(bro(son(e))));
    }
    case offset_div_tag :
    case offset_div_by_int_tag : {
      return (evalexp(son(e))/evalexp(bro(son(e))));
    }
    case offset_subtract_tag : {
      return (evalexp(son(e))-evalexp(bro(son(e))));
    }
    case offset_negate_tag : {
      return (- evalexp(son(e)));
    }

    case bitf_to_int_tag : {
      return ( evalexp ( son ( e ) ) ) ;
    }
    
    case int_to_bitf_tag : {
      ash a ;
      unsigned long w = ( unsigned long ) evalexp ( son ( e ) ) ;
      a = ashof ( sh ( e ) ) ;
      if ( a.ashalign != 1 && !( name ( sh ( e ) ) == cpdhd &&
				 a.ashalign == 32 ) ) {
	fail ( "Illegal bitfield constant" ) ;
      }
				 if ( a.ashsize != 32 ) {
				   w &= ( ( 1 << a.ashsize ) - 1 ) ;
				 }
				 return ( ( long ) w ) ;
    }
    
    case not_tag : {
      long a1 = evalexp ( son ( e ) ) ;
      return ( ~a1 ) ;
    }
    
    case and_tag : {
      long a1 = evalexp ( son ( e ) ) ;
      long a2 = evalexp ( bro ( son ( e ) ) ) ;
      return ( a1 & a2 ) ;
    }
    
    case or_tag : {
      long a1 = evalexp ( son ( e ) ) ;
      long a2 = evalexp ( bro ( son ( e ) ) ) ;
      return ( a1 | a2 ) ;
    }

    case xor_tag : {
      long a1 = evalexp ( son ( e ) ) ;
      long a2 = evalexp ( bro ( son ( e ) ) ) ;
      return ( a1 ^ a2 ) ;
    }

    case shr_tag : {
      bool sgned = ( bool ) ( name ( sh ( e ) ) & 1 ) ;
      long a1 = evalexp ( son ( e ) ) ;
      long a2 = evalexp ( bro ( son ( e ) ) ) ;
      if ( sgned ) {
	return ( a1 >> a2 ) ;
      } 
      else {
	unsigned long b1 = ( unsigned long ) a1 ;
	return ( ( long ) ( b1 >> a2 ) ) ;
      }
    }
    
    case shl_tag : {
      long a1 = evalexp ( son ( e ) ) ;
      long a2 = evalexp ( bro ( son ( e ) ) ) ;
      return ( a1 << a2 ) ;
    }
    
    case concatnof_tag : {
      ash s1, s2 ;
      unsigned long a1 = ( unsigned long ) evalexp ( son ( e ) ) ;
      unsigned long a2 = ( unsigned long ) evalexp ( bro ( son ( e ) ) ) ;
      s1 = ashof ( sh ( son ( e ) ) ) ;
      s2 = ashof ( sh ( bro ( son ( e ) ) ) ) ;
    
      /* We should only be concatenating bitfields */
      assert ( s1.ashalign == 1 && s1.ashsize <= 32 ) ;
      assert ( s2.ashalign == 1 && s2.ashsize <= 32 ) ;
      assert ( s1.ashsize + s2.ashsize <= 32 ) ;
    
      if ( s2.ashsize == 32 ) {
	/* avoid illegal shift by 32 */
	assert ( a1 == 0 ) ;
	return ( ( long ) a2 ) ;
      }
      return ( ( long ) ( ( a1 << s2.ashsize ) | a2 ) ) ;
    }
    
    case clear_tag : {
      return ( 0 ) ;
    }
  }
  fail ( "Illegal integer constant" ) ;
  return ( 0 ) ;
}


/*
  OUTPUT A SIMPLE VALUE
*/
static void oneval 
    PROTO_N ( ( val, al, rep ) )
    PROTO_T ( int val X long al X int rep ){
  char *as ;
  if ( al <= 8 ) {
    as = "\t.byte\t" ;
  } 
  else if ( al <= 16 ) {
    as = "\t.half\t" ;
  } 
  else {
    as = "\t.word\t" ;
  }
  assert ( rep == 1 ) ;
  outs ( as ) ;
  outn ( val ) ;
  outnl () ;
  return ;
}


/*
  OUTPUT A STRING
*/
static void outascii 
    PROTO_N ( ( s, strsize ) )
    PROTO_T ( char * s X long strsize ){
  while ( strsize > 0 ) {
    int i ;
    outs ( "\t.ascii\t\"" ) ;
    for ( i = 0 ; strsize > 0 && i < 48 ; i++ ) {
      int c = ( int ) *s ;
      switch ( c ) {
	case '"'  : outs ( "\\\"" ) ; break ;
	case '\\' : outs ( "\\\\" ) ; break ;
	case '\t' : outs ( "\\t" ) ; break ;
	case '\n' : outs ( "\\n" ) ; break ;
	case '\r' : outs ( "\\r" ) ; break ;
	case '\f' : outs ( "\\f" ) ; break ;
	case '\b' : outs ( "\\b" ) ; break ;
	default : {
	  if ( c >= 0 && isprint ( c ) ) {
	    outc ( c ) ;
	  } 
	  else {
	    /* octal representation */
	    outf ( "\\%.3o", (unsigned)c & 0xff ) ;
	  }
	  break ;
	}
      }
      s++ ;
      strsize-- ;
    }
    outs ( "\"\n" ) ;
  }
  return ;
}


/*
    TYPE REPRESENTING BIT PATTERNS
*/

typedef struct {
  int bitposn ;
  int value_size ;
  unsigned long value ;
} concbittype ;


/*
    FORM AN EMPTY BIT PATTERN
*/
static concbittype emptyconcbit 
    PROTO_N ( ( bitposn ) )
    PROTO_T ( int bitposn ){
  concbittype start ;
  start.bitposn = bitposn ;
  start.value_size = 0 ;
  start.value = 0 ;
  return ( start ) ;
}	


/*
  OUTPUT A BIT PATTERN
*/
static void outconcbit 
    PROTO_N ( ( c, ro ) )
    PROTO_T ( concbittype c X bool ro ){
  unsigned long w = c.value ;
  int sz = c.value_size ;
  int i, bytes = ( sz + 7 ) / 8 ;
  if (ro)
    insection ( rodata_section ) ;
  else
    insection ( data_section ) ;
  if ( sz == 0 ) return ;
  assert ( sz <= 32 ) ;
  
  /* output as a series of bytes */
  outs ( "\t.byte\t" ) ;
#if little_end
  for ( i = 0 ; i < bytes ; i++ ) {
    if ( i != 0 ) outc ( ',' ) ;
    outf ( "%#lx", w & 0xff ) ;
    w = w >> 8 ;
  }
#else
    /* shift to left end of word */
  if ( sz != 32 ) w = w << ( 32 - sz ) ;
  for ( i = 0 ; i < bytes ; i++ ) {
    if ( i != 0 ) outc ( ',' ) ;
    outf ( "%#lx", ( w >> 24 ) & 0xff ) ;
    w = w << 8 ;
  }
#endif
  outnl () ;
  assert ( w == 0 ) ;
  return ;
}

/*
  Output a unary representation of the number val.  val should be 
  less than or equal to 31 as it represent the number of bits
  in a bitfield which does not occupy a whole machine word.
*/
long unary 
    PROTO_N ( ( val ) )
    PROTO_T ( int val ){
  int loop;
  long result=0;
  assert (val <=31);
  for(loop=0;loop<val;++loop){
    result <<=1;
    result |= 1;
  }
  return result;
}



/*
  ADD A VALUE TO A BIT PATTERN
*/

static concbittype addconcbitaux 
    PROTO_N ( ( w, size, b4, ro ) )
    PROTO_T ( unsigned long w X int size X concbittype b4 X bool ro ){
  int wordpos ; /* bit position within word */
  if ( b4.value_size == 32 ||
       ( b4.value_size != 0 && ( b4.bitposn & 31 ) == 0 ) ) {
    assert ( ( b4.bitposn & 31 ) == 0 ) ;
    wordpos = 32 ;
  } 
  else {
    wordpos = ( b4.bitposn & 31 ) ;
  }
  assert ( size > 0 ) ;
  assert ( size <= 32 ) ;
  assert ( b4.value_size <= 32 ) ;
  assert ( wordpos == 0 || b4.value_size <= wordpos ) ;
  if ( ( size == 0 && ( wordpos != 0 || b4.value_size != 0 ) ) ||
       ( wordpos + size > 32 ) ) {
    assert ( wordpos == 32 ) ; /* should be aligned automatically */
    
    /* crossed boundary : output value */
    outconcbit ( b4, ro ) ;
    
    /* start new value */
    b4.value_size = 0 ;
    b4.value = 0 ;
    assert ( ( b4.bitposn & 31 ) == 0 ) ;
  }
  if ( size == 0 ) return ( b4 ) ;
  /* add to b4 */
  if ( size == 32 ) {
    b4.value = w ;
  } 	
  else {
#if little_end
    b4.value = b4.value | ( w << b4.value_size ) ;
#else
    b4.value = ( b4.value << size ) | (w & unary(size));
#endif
  }
  b4.bitposn += size ;
  b4.value_size += size ;
  assert ( b4.value_size <= 32 ) ;
  return ( b4 ) ;
}	


/*
  EVALUATE A CONSTANT BIT PATTERN
*/
static concbittype evalconcbitaux 
    PROTO_N ( ( e, b4, ro ) )
    PROTO_T ( exp e X concbittype b4 X bool ro ){
  switch ( name ( e ) )    {
    case concatnof_tag : {
      concbittype lhs, rhs ;
      lhs = evalconcbitaux ( son ( e ), b4, ro ) ;
      rhs = evalconcbitaux ( bro ( son ( e ) ), lhs, ro ) ;
      return ( rhs ) ;
    }
    default : {
      int size = shape_size ( sh ( e ) ) ;
      unsigned ev = ( unsigned ) evalexp ( e ) ;
      assert ( shape_align ( sh ( e ) ) == 1 ) ;
      return ( addconcbitaux ( ev, size, b4, ro ) ) ;
    }
  }
}


/*
  OUTPUT A CONSTANT BIT PATTERN
*/
static void evalconcbit 
    PROTO_N ( ( e, bitposn, ro ) )
    PROTO_T ( exp e X int bitposn X bool ro ){
  concbittype start ;
  start = emptyconcbit ( bitposn ) ;
  outconcbit ( evalconcbitaux ( e, start, ro ), ro ) ;
  return ;
}


/*
  DOES AN EXPRESSION REPRESENT ZERO?
*/

#if 1

#define is_zero( e )	is_comm ( e )

#else

bool is_zero 
    PROTO_N ( ( e ) )
    PROTO_T ( exp e ){
  if ( e == nilexp ) return ( 1 );
  switch ( name ( e ) ) {
    case null_tag : return ( 1 ) ;
    case val_tag : return ( no ( e ) == 0 ? 1 : 0 ) ;
    case ncopies_tag :
    case int_to_bitf_tag : {
      return ( is_zero ( son ( e ) ) ) ;
    }
    case compound_tag : {
      e = bro ( son ( e ) ) ;
      while ( 1 ) {
	if ( is_zero ( e ) == 0 ) return ( 0 ) ;
	if ( last ( e ) ) return ( 1 ) ;
	e = bro ( bro ( e ) ) ;
      }
      /* NOT REACHED */
    }
    case real_tag : {
      flt f ;
      f = flptnos [ no ( e ) ] ;
      if ( f.exp == 0 ) {
	int i ;
	for ( i = 0 ; i < MANT_SIZE ; i++ ) {
	  if ( f.mant [i] != 0 ) return ( 0 ) ;
	}
	return ( 1 ) ;	 /* all zero */
      }
      return ( 0 ) ;
    }
  }
  return ( 0 ) ;
}

#endif


/*
    OUTPUT AN ALIGNMENT
*/
static void set_align 
    PROTO_N ( ( al ) )
    PROTO_T ( long al ){
#if 0
  assert ( al >= 8 && al <= 64 ) ;
#endif
  if ( al > 8 ) {
    outs ( "\t.align\t" ) ;
    outn ( al / 8 ) ;
    outnl () ;
  }
  return ;
}

 
/*
    EVALUATE AN EXPRESSION
*/
void evalone 
    PROTO_N ( ( e, bitposn, ro ) )
    PROTO_T ( exp e X int bitposn X bool ro ){
  long al = ( long ) shape_align ( sh ( e ) ) ;
  long sz = ( long ) shape_size ( sh ( e ) ) ;
  if (ro)
    insection ( rodata_section ) ;
  else
    insection ( data_section ) ;
  set_align ( al ) ;
  if ( al != 0 ) bitposn = ( int ) ( ( bitposn / al ) * al ) ;
  switch ( name ( e ) ) {
    case string_tag : {
      /* Strings or arrays of integers */
      int i, j ;
      long char_size = ( long ) props ( e ) ;
      long strsize = sz / char_size ;
      char *st = nostr ( e ) ;
      if ( char_size == 8 ) {
	outascii ( st, strsize ) ;
	return ;
      }
      if ( strsize > 0 ) set_align ( char_size ) ;
      for ( j = 0 ; j < strsize ; /**/ ) {
	switch ( char_size ) {
	  case 8 : {
	    outs ( "\t.byte\t" ) ;
	    break ;
	  }
	  case 16 : {
	    outs ( "\t.half\t" ) ;
	    break ;
	  }
	  case 32 : {
	    outs ( "\t.word\t" ) ;
	    break ;
	  }
	}
	/* output chars in batches */
	for ( i = j ; i < strsize && i - j < 8 ; i++ ) {
	  if ( i != j ) outc ( ',' ) ;
	  switch ( char_size ) {
	    case 8 : {
	      outf ( "0x%x", st [i] ) ;
	      break ;
	    }
	    case 16 : {
	      outf ( "0x%x", ( ( short * ) st ) [i] ) ;
	      break ;
	    }
	    case 32 : {
	      outf ( "0x%x", ( ( int * ) st ) [i] ) ;
	      break ;
	    }
	  }
	}
	outnl () ;
	j = i ;
      }
    return ;
    }
    case real_tag : {
      /* Floating point constant */
      flt *f = flptnos + no ( e ) ;
      r2l v;
      if ( sz == 32 ) {
	v = real2longs_IEEE(f,0);
	outs ( "\t.word\t" ) ;
	outn ( v.i1 ) ;
      } 
      else if ( sz == 64 ) {
	v = real2longs_IEEE(f,1);
	outs ( "\t.word\t" ) ;
	outn ( v.i2 ) ;
      outc ( ',' ) ;
      outn ( v.i1 ) ;
      } 
      else {
	v = real2longs_IEEE(f,2);
	outs ( "\t.word\t" ) ;
	outn ( v.i4 ) ;
	outc ( ',' ) ;
	outn ( v.i3 ) ;
	outc ( ',' ) ;
	outn ( v.i2 ) ;
	outc ( ',' ) ;
	outn ( v.i1 ) ;
      }
      outnl () ;
      return ;
    }
    case null_tag : {
      /* Zero */
      no ( e ) = 0 ;
      /* Fall through */
    }
    case val_tag : {
      if(name(sh(e)) == s64hd || name(sh(e)) == u64hd){
	flt64 bval;
	bval = exp_to_f64(e);
	oneval(bval.small,32,1);
	oneval(bval.big,32,1);
      }
      /* Integer constant */
      if(al2(sh(e))>=8 && name(sh(e)) == offsethd){
	no(e) = no(e)>>3;
      }
      if ( al == 1 ) {
	evalconcbit ( e, bitposn, ro ) ;
      } 
      else {
	oneval ( no ( e ), al, 1 ) ;
      }
      return ;
    }
    case name_tag : {
      /* Global name */
      dec *globdec = brog ( son ( e ) ) ;
      char *nm = globdec->dec_u.dec_val.dec_id ;
      outs ( "\t.word " ) ;
      outs ( nm ) ;
      if ( no ( e ) ) {
	outc ( '+' ) ;
	outn ( no ( e ) / 8 ) ;
      }
      outnl () ;
      return ;
    }
    case compound_tag : {
      /* Compound values */
      exp off = son ( e ) ;
      exp tup = bro ( off ) ;
      concbittype left ;
      long last_offset = 0 ;
      long last_align = 0 ;
      long ta = ( long ) shape_align ( sh ( tup ) ) ;
      long ts = shape_size ( sh ( tup ) ) ;
      left = emptyconcbit ( bitposn ) ;
      /* output elements of aggregate recursively */
      while ( 1 ) {
	long noff = no ( off ) ;
	long gap = noff - left.bitposn ;
	/* check that component's alignment matches offset in struct */
	assert ( ( noff / ta ) * ta <= noff ) ;
	assert ( ta <= al ) ;
	if(ts == 0){
	  if(last(tup)) return;
	  else {
	    off = bro ( bro ( off ) ) ;
	    assert ( !last ( off ) ) ;
	    tup = bro ( off ) ;
	    ta = ( long ) shape_align ( sh ( tup ) ) ;
	    ts = shape_size ( sh ( tup ) ) ;
	    continue;
	  }
	}
	/* and is no greater that struct's alignment */
	if ( noff < last_offset ) {
	  fail ( "Compound components badly ordered" ) ;
	}
	if ( last_align <= 1 || ta <= 1 || gap >= ta ) {
	  /* get gap down */
	  while ( gap > 0 ) {
	    left = addconcbitaux ( 0, 1, left, ro ) ;
	    gap-- ;
	  }
	} 
        else {
	  /* alignment will handle gap */
	  left.bitposn = ( int ) rounder ( left.bitposn, ta ) ;
	}
	last_offset = noff ;
	last_align = ta ;
	assert ( left.bitposn - bitposn == noff ) ;
	if ( ta == 1 ) {
	  /* collect bitfields */
	  left = evalconcbitaux ( tup, left, ro ) ;
	} 
        else {
	/* output final bits from any previous field */
	  int lb ;
	  outconcbit ( left, ro ) ;
	  lb = left.bitposn ;
	  left = emptyconcbit ( lb ) ;
	  evalone ( tup, left.bitposn, ro ) ;
	  left.bitposn = ( int ) ( left.bitposn + ts ) ;
	}
	if ( last ( tup ) ) {
	  /* output final bits from any previous field */
	  long databits = no ( off ) + ts ;
	  long trailing_bytes = ( sz - databits ) / 8 ;
	  outconcbit ( left, ro ) ;
	  assert ( sz >= databits ) ;
	  /* pad out trailing uninitialised space, eg union */
	  if ( sz > databits && trailing_bytes > 0 ) {
	    outs ( "\t.skip\t" ) ;
	    outn ( trailing_bytes ) ;
	    outnl () ;
	  }
	  return ;
	}
	off = bro ( bro ( off ) ) ;
	assert ( !last ( off ) ) ;
	tup = bro ( off ) ;
	ta = ( long ) shape_align ( sh ( tup ) ) ;
	ts = shape_size ( sh ( tup ) ) ;
      }
      /* NOT REACHED */
    }
    case nof_tag : {
      /* Arrays */
      exp s = son ( e ) ;
      set_align ( al ) ;
      for ( ; ; ) {
	evalone ( s, bitposn, ro ) ;
	if ( last ( s ) ) return ;
	s = bro ( s ) ;
      }
      /* NOT REACHED */
    }
    case ncopies_tag : {
      /* Multiple copies */
      ash c ;
      int i, n = no ( e ) ;
      while ( name ( son ( e ) ) == ncopies_tag ) {
	e = son ( e ) ;
	n *= no ( e ) ;
      }
      e = son ( e ) ;
      c = ashof ( sh ( e ) ) ;
#if 0
      if ( c.ashalign != 0 ) {
	bitsize = ( c.ashsize / c.ashalign ) * c.ashalign ;
      } 
      else {
	bitsize = 0 ;
      }
#endif
      if ( is_zero ( e ) ) {
	set_align ( al ) ;
	outs ( "\t.skip\t" ) ;
	outn ( ( sz + 7 ) >> 3 ) ;
	outnl () ;
      }
      else
        for ( i = 0 ; i < n ; i++ ) evalone ( e, bitposn, ro ) ;
      return ;
    }
    case concatnof_tag : {
      /* Concatenation of arrays */
      if ( al == 1 ) {
	/* allow for bitfields */
	evalconcbit ( e, bitposn, ro ) ;
      } 
      else {
	ash a ;
	a = ashof ( sh ( son ( e ) ) ) ;
	evalone ( son ( e ), bitposn, ro ) ;
	bitposn = ( int ) ( bitposn + a.ashsize ) ;
	a = ashof ( sh ( bro ( son ( e ) ) ) ) ;
	if ( a.ashalign != 0 ) {
	  bitposn = ( int ) ( ( bitposn / a.ashalign ) *
			      a.ashalign ) ;
	}	
	evalone ( bro ( son ( e ) ), bitposn, ro ) ;
      }
      return ;
    }
    case clear_tag : {
      if ( al == 1 ) {
	/* allow for bitfields */
	evalconcbit ( e, bitposn, ro ) ;
	return ;
      }
      outs ( "\t.skip\t" ) ;
      outn ( ( sz + 7 ) >> 3 ) ;
      outnl () ;
      return ;
    }
    case not_tag :
    case and_tag :
    case or_tag :
    case shl_tag :
    case shr_tag :
    case bitf_to_int_tag :
    case int_to_bitf_tag :
    case general_env_offset_tag :
    case env_offset_tag : 
    case env_size_tag : case offset_add_tag : case offset_max_tag :
    case offset_pad_tag : case offset_mult_tag : case offset_div_tag :
    case offset_div_by_int_tag : case offset_subtract_tag : 
    case offset_negate_tag : {
      outs ( "\t.word\t" ) ;
      outn ( evalexp ( e ) ) ;
      outnl () ;
      return ;
    }
    
    case chvar_tag : {
      if ( shape_size ( sh ( e ) ) == shape_size ( sh ( son ( e ) ) ) ) {
	sh ( son ( e ) ) = sh ( e ) ;
	evalone ( son ( e ), bitposn, ro ) ;
      } 
      else {
	fail ( "Illegal chvar constant" ) ;
      }
      return ;
    }

    case minptr_tag : {
      exp p1 = son ( e ) ;
      exp p2 = bro ( p1 ) ;
      if ( name ( p1 ) == name_tag && name ( p2 ) == name_tag ) {
	long n = no ( p1 ) - no ( p2 ) ;
	char *n1 = brog ( son ( p1 ) )->dec_u.dec_val.dec_id ;
	char *n2 = brog ( son ( p2 ) )->dec_u.dec_val.dec_id ;
	outs ( "\t.word\t" ) ;
	outs ( n1 ) ;
	outs ( "-" ) ;
	outs ( n2 ) ;
	if ( n < 0 ) {
	  outn ( n ) ;
	} 
        else if ( n > 0 ) {
	  outc ( '+' ) ;
	  outn ( n ) ;
	}
	outnl () ;
	return ;
      }
      /* FALL THROUGH */
    }

    default : {
      fail ( "Illegal constant" ) ;
      return ;
    }
  }
}


/*
  FLAG
*/
bool know_size = 0 ;


/*
  OUTPUT DATA INITIALISERS FOR AN EXPRESSION
  The result is the instore address of the constant.  A negative 
  value of ll indicates the initialisation of a global variable.
*/
instore evaluated 
    PROTO_N ( ( e, ll, ro ) )
    PROTO_T ( exp e X long ll X bool ro ){
  ash a ;
  int lab ;
  exp z = e ;
  instore isa ;
  bool extnamed ;
  know_size = 0 ;
  if ( ll == 0 ) {
    lab = next_data_lab () ;
    extnamed = 0 ;
  } 
  else if ( ll < 0 ) {
    lab = ( int ) ll ;
    extnamed = ( bool ) main_globals [ -lab - 1 ]->dec_u.dec_val.extnamed ;
  } 
  else /* if ( ll > 0 ) */ {
    lab = ( int ) ( -ll ) ;
    extnamed = ( bool ) main_globals [ -lab - 1 ]->dec_u.dec_val.extnamed ;
  }
  a = ashof ( sh ( e ) ) ;
  
  isa.adval = 0 ;
  isa.b.offset = 0 ;
  isa.b.base = lab ;
  if ( is_zero ( e ) ) {
    int byte_size = ( int ) ( ( a.ashsize + 7 ) >> 3 ) ;
    int align = ( ( a.ashalign > 32 || a.ashsize > 32 ) ? 8 : 4 ) ;
    if ( !extnamed || (name(e) == clear_tag && no(e) == -1) ||
		/* SUNOS simplifies extraction of .common from library modules */
	 (!sysV_assembler && dynamic_init_proc != (char *)0 &&
		!(main_globals [ -lab - 1 ]->dec_u.dec_val.is_common))
	) {
      outs ( "\t.reserve\t" ) ;
      outlab ( lab ) ;
      if ( sysV_assembler ) {
	outc ( ',' ) ;
	outn ( byte_size ) ;
	outs ( ",\".bss\"," ) ;
	outn ( align ) ;
	outnl () ;
      } 
      else {
	outc ( ',' ) ;
	outn ( byte_size ) ;
	outs ( ",\"bss\"," ) ;
	outn ( align ) ;
	outnl () ;
      }
#ifdef NEWDWARF
      if (dwarf2 && (name(e) == clear_tag && no(e) == -1))
        note_data (lab, ro);	/* do_prom */
#endif
    } 
    else {
      if ( a.ashalign > 32 || a.ashsize > 32 ) {
	set_align ( 64L ) ;
      } 
      else {
	set_align ( 32L ) ;
      }
      outs ( "\t.common\t" ) ;
      outlab ( lab ) ;
      if ( sysV_assembler ) {
	outc ( ',' ) ;
	outn ( byte_size ) ;
	outc ( ',' ) ;
	outn ( align ) ;
	outnl () ;
      } 
      else {
	outc ( ',' ) ;
	outn ( byte_size ) ;
	outnl () ;
      }
    }
    know_size = 1 ;
  } 
  else {
#ifdef NEWDWARF
    if (dwarf2)
      note_data (lab, ro);
#endif
    if (ro)
      insection ( rodata_section ) ;
    else
      insection ( data_section ) ;
    if ( a.ashalign > 32 || a.ashsize > 32 ) {
      set_align ( 64L ) ;
    } 
    else {
      set_align ( 32L ) ;
    }
    outlab ( lab ) ;
    outs ( ":\n" ) ;
    if(a.ashsize != 0){
      evalone ( z, 0, ro ) ;
    }
    /* evalone does not output .skip to finish off */
    if ( a.ashalign > 32 ) set_align ( 64L ) ;
    /* return to .text for local values */
    if ( ll >= 0 ) insection ( text_section ) ;
  }
  return ( isa ) ;
}
