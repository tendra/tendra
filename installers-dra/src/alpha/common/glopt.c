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


#include "config.h"
#include "common_types.h"
#include "tags.h"
#include "externs.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "exp.h"
#include "basicread.h"
#include "flags.h"
#include "table_fns.h"
#include "installglob.h"
#include "check.h"
#include "glopt.h"


/*
  disabled temporarily - this function replaces calls to the 
  strcpy function with a direct mem -> mem copy.
*/


void glopt
    PROTO_N ( ( dp ) )
    PROTO_T ( dec *dp )
{
#if 0
  if (!strcmp(dp -> dec_u.dec_val.dec_id, "strcpy"))
  {
    exp i = dp -> dec_u.dec_val.dec_exp;
    exp t = pt(i);
    if (t == nilexp)
      return;
    
    while (1)
    {
      if (!last(t) && !last(bro(t)) && last(bro(bro(t))) &&
	  name(bro(bro(bro(t)))) == apply_tag &&
	  son(bro(bro(bro(t)))) == t){
	exp dest = bro(t);
	exp source = bro(dest);
	
	if (name(source) == name_tag && isglob(son(source)) &&
	    isvar(son(source)) && no(son(source)) == 1){
	  dec * source_dec = brog(son(source));
	  if (!source_dec -> dec_u.dec_val.extnamed &&
	      son(source_dec -> dec_u.dec_val.dec_exp) != nilexp){
	    exp source_def = son(son(source));
	    shape sha = sh(source_def);
	    if (name(source_def) == string_tag &&
		ptno(source_def) == 8){
	      char * s = nostr(source_def);
	      int n, j;
	      int l = shape_size(sha) / 8;
	      for (j=0; j < l && s[j] != 0; ++j);
	      if (j < l){
		exp q;
		exp to_change = bro(source);
		exp idsc = getexp(sh(bro(source)), nilexp, 0,
				  dest, nilexp,
				  0, 2, ident_tag);
		exp n1 = getexp(sh(dest), nilexp, 0, idsc,
				nilexp, 0, 0, name_tag);
		exp n2 = getexp(sh(dest), nilexp, 0, idsc, n1,
				0, 0, name_tag);
		exp_list el;

		pt(idsc) = n2;

		q = f_assign(n1, f_contents(sha, source));
		el.start = q;
		el.end = q;
		el.number = 1;
		q = f_sequence(el, n2);
		clearlast(dest);
		bro(dest) = q;
		setfather(idsc, q);
		replace(to_change, idsc, idsc);
		t = pt(i);
	      }
	    }
	  }
	}
      }
      if (pt(t) == nilexp)
	return;
      t = pt(t);
    };
  };
#endif
  return;
}






