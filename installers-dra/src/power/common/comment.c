/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include "translat.h"	/* for as_file */
#include "comment.h"

bool do_comment;			/* set in powertrans.c */

#ifdef DO_COMMENT

void COMMENT(char *mess)
{
  if (do_comment)
  {
    fprintf(as_file, "## %s\n", mess);
  }
}

void COMMENT1(char *mess, long p1)
{
  if (do_comment)
  {
    fprintf(as_file, "## ");
    fprintf(as_file, mess, p1);
    fprintf(as_file, "\n");
  }
}

void COMMENT2(char *mess, long p1, long p2)
{
  if (do_comment)
  {
    fprintf(as_file, "## ");
    fprintf(as_file, mess, p1, p2);
    fprintf(as_file, "\n");
  }
}

void COMMENT3(char *mess, long p1, long p2, long p3)
{
  if (do_comment)
  {
    fprintf(as_file, "## ");
    fprintf(as_file, mess, p1, p2, p3);
    fprintf(as_file, "\n");
  }
}

void COMMENT4(char *mess, long p1, long p2, long p3, long p4)
{
  if (do_comment)
  {
    fprintf(as_file, "## ");
    fprintf(as_file, mess, p1, p2, p3, p4);
    fprintf(as_file, "\n");
  }
}

#else				/* DO_COMMENT */

/* defined as NULL macros in comment.h */

#endif				/* DO_COMMENT */


void fail(char *mess)
{
  COMMENT1("TRANSLATION FAILED: %s", (long) mess);
  fflush(as_file);
  fprintf(stderr, "powertrans: internal error '%s'\n", mess);
  if (!do_comment)
  {
    exit(3);
  }
  /* else go on to generate more code to give the error context */
}
