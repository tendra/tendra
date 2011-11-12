/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

    
    
    
    
    



/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:49:05 $
$Revision: 1.2 $
$Log: record_bit.c,v $
 * Revision 1.2  1998/02/04  15:49:05  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:03:46  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"

#include "maxminmacs.h"
#include "comment.h"
#include "muldvrem.h"
#include "proc.h"
#include "flags.h"
#include "translat.h"
#include "eval.h"

#include "makecode.h"
#include "frames.h"
#include "stack.h"
#include "label_ops.h"
#include "instruct.h"
#include "installglob.h"
#include "externs.h"
#include "tempdecs.h"
#include "diag_fns.h"
#include "oprators.h"
#include "record_bit.h"

#define CASE_RECORD_BIT and_tag:case plus_tag:case shr_tag


void try_record_bit(exp e)
{
  /* Tries to see if record bit can be used in this test_tag*/
  exp l = son(e);
  exp r = bro(l);
  bool sgned = is_signed(sh(l)); 
  
  if (name(r)==val_tag && optop(l) &&
      no(r)==0 &&
      !is_floating(name(sh(l))) &&
      (sgned||test_number(e)==TEST_NE || test_number(e)==TEST_EQ)
      /* The record bit is set as if the comparison where algebraic
	 however we can use TEST_NE and TEST_EQ as well since the
	 concept of equality is the same for signed and unsigned numbers
	 */
      )
  {
    switch(name(l))
    {
     case CASE_RECORD_BIT:
      setrecordbit(l);
    }
  }
  return;
}

bool record_bit_set(exp e)
{
  switch(name(e))
  {
   case CASE_RECORD_BIT:
    return isrecordbit(e);
  }
  return 0;
}
