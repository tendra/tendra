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


/* 	$Id: oddtest.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: oddtest.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $";
#endif /* lint */

/* 
   Pattern in oddtest.pat
   this is intended to be the pattern for:
   if (test) fexp 1 else fexp -1
   to transform to:
   fexp ( (absbool(test) <<1) -1))
   where f is any sequence of unary operators including identity
*/

/*
$Log: oddtest.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/23  10:39:15  john
 * Entered into CVS
 *
 * Revision 1.3  1995/01/26  13:45:30  john
 * Removed unused label
 *
*/

#include "config.h"
#include "tags.h"
#include "common_types.h"
#include "expmacs.h"
#include "exptypes.h"
#include "shapemacs.h"
#include "comp_eq_exp.h"
#include "check.h"
#include "oddtest.h"

static int oddunary
    PROTO_N ( ( x, y, v ) )
    PROTO_T ( exp x X exp y X exp *v )
{
  exp z;
  *v = x;
  if (name(x) != val_tag) goto flab1; 
  if (!(name(y)==val_tag && ((no(x)==1 && no(y)==-1) || (no(x)==-1 && no(y)==1) ))) goto flab1;
  goto tlab1;
 flab1:
  if (!(name(x)==name(y))) goto flab0;
  { exp xC = son(x);
    z = xC;
    if (!(z!=nilexp && last(z) && son(y) != nilexp && oddunary(z, son(y),v))) goto flab0;
    if(!last(xC)) goto flab0;
  }
 tlab1:
  return 1; 
 flab0: return 0; 
}	 

int oddtest
    PROTO_N ( ( x, t, f, v ) )
    PROTO_T ( exp x X exp *t X exp *f X exp *v )
{
  exp l, z, g;
  if (name(x) != cond_tag) goto flab0; 
  { exp xC = son(x);
    if (name(xC) != seq_tag) goto flab0; 
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (name(xCCC) != test_tag) goto flab0; 
        l =pt(*t);
        if(!last(xCCC)) goto flab0;
      }	
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      *f = xCC;
      if(!last(xCC)) goto flab0;
    }	
    if (last(xC)) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      g = xCC;
      if (!(oddunary(*f,g,v))) goto flab0;
      if(!last(xCC)) goto flab0;
    }
    if(!last(xC)) goto flab0;
  }
  return 1; 
  flab0: return 0; 
} 

/* last_statement finds the last obeyed statement of x and puts it in f */
int last_statement
    PROTO_N ( ( x, f ) )
    PROTO_T ( exp x X exp *f )
{
  exp z;
  if (name(x) != ident_tag) goto flab1; 
  { exp xC = son(x);
    if (last(xC)) goto flab1;
    xC = bro(xC);
    z = xC;
    last_statement(z, f);
    if(!last(xC)) goto flab1;
  }
  goto tlab1;
  flab1:
  if (name(x) != seq_tag) goto flab2; 
  { exp xC = son(x);
    if (last(xC)) goto flab2;
    xC = bro(xC);
    z = xC;
    last_statement(z, f);
    if(!last(xC)) goto flab2;
  }
  goto tlab1;
  flab2:
  z = x;
   *f = z;
  tlab1:
  return 1; 
} 


int is_maxlike
    PROTO_N ( ( x, t ) )
    PROTO_T ( exp x X exp *t )
{
  exp op1, op2, z, l, w;
  if (name(x) != cond_tag) goto flab0; 
  { exp xC = son(x);
    if (name(xC) != seq_tag) goto flab0; 
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (name(xCCC) != test_tag) goto flab0; 
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op1 = xCCCC;
          if (!(!is_floating(name(sh(op1))))) goto flab0;
          if (last(xCCCC)) goto flab0;
          xCCCC = bro(xCCCC);
          op2 = xCCCC;
          if(!last(xCCCC)) goto flab0;
        }
        if(!last(xCCC)) goto flab0;
      }
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(comp_eq_exp(z, op1, nilexp,nilexp))) goto flab0;
      if(!last(xCC)) goto flab0;
    }
    if (last(xC)) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      w = xCC;
      if (!(comp_eq_exp(w, op2,nilexp,nilexp))) goto flab0;
      if(!last(xCC)) goto flab0;
    }
    if(!last(xC)) goto flab0;
  }
  return 1; 
  flab0: return 0; 
} 


int is_minlike
    PROTO_N ( ( x, t ) )
    PROTO_T ( exp x X exp *t )
{
  exp op1, op2, z, l, w;
  if (name(x) != cond_tag) goto flab0; 
  { exp xC = son(x);
    if (name(xC) != seq_tag) goto flab0; 
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (name(xCCC) != test_tag) goto flab0; 
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op1 = xCCCC;
          if (!(!is_floating(name(sh(op1))))) goto flab0;
          if (last(xCCCC)) goto flab0;
          xCCCC = bro(xCCCC);
          op2 = xCCCC;
          if(!last(xCCCC)) goto flab0;
        }
        if(!last(xCCC)) goto flab0;
      }
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(comp_eq_exp(z, op2,nilexp,nilexp))) goto flab0;
      if(!last(xCC)) goto flab0;
    }
    if (last(xC)) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      w = xCC;
      if (!(comp_eq_exp(w, op1,nilexp,nilexp))) goto flab0;
      if(!last(xCC)) goto flab0;
    }
    if(!last(xC)) goto flab0;
  }
  return 1; 
  flab0: return 0; 
} 

/* looks for things like
	(a~0) ? a:-a
*/
int is_abslike
    PROTO_N ( ( x,t ) )
    PROTO_T ( exp x X exp *t )
{
  exp op, l, z, w;
  if (name(x) != cond_tag) goto flab0; 
  { exp xC = son(x);
    if (name(xC) != seq_tag) goto flab0; 
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (name(xCCC) != test_tag) goto flab0; 
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op = xCCCC;
          if (last(xCCCC)) goto flab0;
          xCCCC = bro(xCCCC);
          if (name(xCCCC) != val_tag || no(xCCCC) != 0) goto flab0;
          if(!last(xCCCC)) goto flab0;
        }
        if(!last(xCCC)) goto flab0;
      }
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(comp_eq_exp(z, op,nilexp,nilexp))) goto flab0;
      if(!last(xCC)) goto flab0;
    }
    if (last(xC)) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      if (name(xCC) != neg_tag) goto flab0; 
      { exp xCCC = son(xCC);
        w = xCCC;
        if (!(comp_eq_exp(op, w,nilexp,nilexp))) goto flab0;
        if(!last(xCCC)) goto flab0;
      }
      if(!last(xCC)) goto flab0;
    }
    if(!last(xC)) goto flab0;
  }
  return 1; 
  flab0: return 0; 
} 



int is_fabs
    PROTO_N ( ( x, t ) )
    PROTO_T ( exp x X exp *t )
{
  exp op, l, z, w;
  if (name(x) != cond_tag) goto flab0; 
  { exp xC = son(x);
    if (name(xC) != seq_tag) goto flab0; 
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (name(xCCC) != test_tag) goto flab0; 
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op = xCCCC;
          if (last(xCCCC)) goto flab0;
          xCCCC = bro(xCCCC);
          if (name(xCCCC) != val_tag || no(xCCCC) != 0) goto flab0;
          if(!last(xCCCC)) goto flab0;
        }
        if(!last(xCCC)) goto flab0;
      }
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(eq_exp(z, op))) goto flab0;
      if(!last(xCC)) goto flab0;
    }
    if (last(xC)) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      if (name(xCC) != fneg_tag) goto flab0; 
      { exp xCCC = son(xCC);
        w = xCCC;
        if (!(eq_exp(op, w))) goto flab0;
        if(!last(xCCC)) goto flab0;
      }
      if(!last(xCC)) goto flab0;
    }
    if(!last(xC)) goto flab0;
  }
  return 1; 
  flab0: return 0; 
} 

