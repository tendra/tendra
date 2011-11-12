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
$Date: 1998/02/04 15:48:43 $
$Revision: 1.2 $
$Log: dynamic_init.c,v $
 * Revision 1.2  1998/02/04  15:48:43  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:00:18  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


/* dynamic_init.c does all the dynamic initialisation code
 */
#include "config.h"
#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "translat.h"
#include "makecode.h"
#include "machine.h"
#include "flags.h"
#include "comment.h"
#include "proc.h"
#include "stack.h"
#include "parameter.h"
#include <shared/error.h>
#include "installglob.h"
#include "dynamic_init.h"

void do__main_extern(void)
{
  fprintf(as_file,"\t.extern\t__main\n");
  fprintf(as_file,"\t.extern\t.__main\n");
}

void call__main(void)
{
  fprintf(as_file,"\tbl\t.__main\n");
  fprintf(as_file,"\tcror\t15,15,15\n");
}
int proc_is_main(exp e)
{
  baseoff b;
  char *ext;
  b = boff(father(e));
  ext = main_globals[(-b.base)-1]->dec_u.dec_val.dec_id;
  if (strcmp(ext,"main")==0)
  {
    return 1;
  }
  return 0;
}
