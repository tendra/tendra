/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include <local/exp.h>

#include <tdf/tag.h>

#include <reader/externs.h>

#include <construct/label_ops.h>
#include <construct/installglob.h>

#include <main/flags.h>

#include <diag3/diag_fns.h>

#include "procrec.h"
#include "geninst.h"
#include "muldvrem.h"
#include "proc.h"
#include "translate.h"
#include "eval.h"
#include "make_code.h"
#include "frames.h"
#include "stack.h"
#include "instruct.h"
#include "tempdecs.h"
#include "ops.h"
#include "record_bit.h"

#define CASE_RECORD_BIT and_tag:case plus_tag:case shr_tag


void try_record_bit(exp e)
{
  /* Tries to see if record bit can be used in this test_tag*/
  exp l = son(e);
  exp r = bro(l);
  bool sgned = is_signed(sh(l)); 
  
  if (r->tag==val_tag && optop(l) &&
      no(r)==0 &&
      !is_floating(sh(l)->tag) &&
      (sgned||test_number(e)==TEST_NE || test_number(e)==TEST_EQ)
      /* The record bit is set as if the comparison where algebraic
	 however we can use TEST_NE and TEST_EQ as well since the
	 concept of equality is the same for signed and unsigned numbers
	 */
      )
  {
    switch (l->tag)
    {
     case CASE_RECORD_BIT:
      setrecordbit(l);
    }
  }
}

bool record_bit_set(exp e)
{
  switch (e->tag)
  {
   case CASE_RECORD_BIT:
    return isrecordbit(e);
  }
  return 0;
}
