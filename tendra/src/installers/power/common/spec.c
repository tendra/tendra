/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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



/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:49:09 $
$Revision: 1.2 $
$Log: spec.c,v $
 * Revision 1.2  1998/02/04  15:49:09  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:04:20  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


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
#include "spec.h"


speci special_fn PROTO_N ((a1, a2, s)) PROTO_T (exp a1 X exp a2 X shape s)
{				/* look for special functions */
  speci spr;
  dec* dp = brog (son (a1));
  char *id = dp -> dec_u.dec_val.dec_id;
  spr.is_special = 0;
  if (id == (char *) 0)
    return (spr);
  /* at present the detection of special cases is done on the identifiers,
     but it really ought to be on special tokens, as for diagnostics */

  if (!strcmp (id, "setjmp"))
    has_setjmp = 1;

  if (!strcmp (id, "longjmp"))
    has_setjmp = 1;

     /* we must always set has_setjmp if it is longjmp,
        otherwise registers are not reset.
        so don't do do_special_fns test until after longjmp test. */
  if (!do_special_fns)
    return spr;

  if (do_alloca &&
      (!strcmp (id, "alloca") || !strcmp (id, "__builtin_alloca"))) {
    exp r = getexp (s, nilexp, 0, a2, nilexp, 0,
	(long) 0, alloca_tag);
    setfather(r, son(r));
    has_alloca = 1;
    spr.is_special = 1;
    spr.special_exp = r;
    kill_exp (a1, a1);
    return (spr);
  };

  return (spr);
}
