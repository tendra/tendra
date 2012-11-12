/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* dynamic_init.c does all the dynamic initialisation code */

#include <string.h>

#include <shared/error.h>

#include "config.h"

#include <construct/machine.h>
#include <construct/flags.h>
#include <construct/installglob.h>

#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "translat.h"
#include "makecode.h"
#include "comment.h"
#include "proc.h"
#include "stack.h"
#include "parameter.h"
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
