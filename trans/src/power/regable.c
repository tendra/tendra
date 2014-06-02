/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This has procedures to determine whether ident exp will fit in a register.
 * Called, for example, by needs scan which uses these procs to decide whether
 * to mark the props of the exp with inreg_bits or infreg_bits or neither.
 */

#include "memtdf.h"
#include "codegen.h"
#include "comment.h"
#include "regable.h"
#include "localexpmacs.h"

bool valregable(shape s)
{
  int n = name(s);

  if (is_floating(n) || IS_AGGREGATE(s))
  {
    /* floats, compound and arreay not generally in fixed reg */
    return 0;
  }
  else
  {
    return shape_size(s)<=32 && n!=tophd;
  }
}

/*
 * Determines whether the exp e can fit in a single fixed point register.
 * Uses macros isvis, isglob, iscaonly from expmacs.h which examine the props
 * field. The iscaonly bit is set by proc independent if the tag is only used
 * by the contents operator or as the left hand side of an assignment.
 *
 * The procedure also uses the macro is_floating from shapemacs.h which checks
 * the shape number is in the range for floating point shapes.
 */
bool fixregable(exp e)
{
  if (!isvis(e) && !isoutpar(e) && !isglob(e) )
  {
    shape s = sh(son(e));	/* son of ident exp is def */

    return valregable(s);
  }
  else
  {
    return 0;
  }
}

/*
 * Determines whether the exp e can fit in a floating point register, single
 * or double.
 */
bool floatregable(exp e)
{
  if (!isvis(e) && !isoutpar(e) && !isglob(e) )
  {
    shape s = sh(son(e));

    return is_floating(name(s));
  }
  else
  {
    return 0;
  }
}
