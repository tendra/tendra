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
$Date: 1998/02/04 15:48:41 $
$Revision: 1.2 $
$Log: comment.c,v $
 * Revision 1.2  1998/02/04  15:48:41  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  15:59:53  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "translat.h"	/* for as_file */
#include "comment.h"
bool do_comment;			/* set in powertrans.c */

#ifdef DO_COMMENT

void COMMENT PROTO_N ((mess)) PROTO_T (char *mess)
{
  if (do_comment)
  {
    fprintf(as_file, "## %s\n", mess);
  }
}

void COMMENT1 PROTO_N ((mess,p1)) PROTO_T (char *mess X long p1)
{
  if (do_comment)
  {
    fprintf(as_file, "## ");
    fprintf(as_file, mess, p1);
    fprintf(as_file, "\n");
  }
}

void COMMENT2 PROTO_N ((mess,p1,p2)) PROTO_T (char *mess X long p1 X long p2)
{
  if (do_comment)
  {
    fprintf(as_file, "## ");
    fprintf(as_file, mess, p1, p2);
    fprintf(as_file, "\n");
  }
}

void COMMENT3 PROTO_N ((mess,p1,p2,p3)) PROTO_T (char *mess X long p1 X long p2 X long p3)
{
  if (do_comment)
  {
    fprintf(as_file, "## ");
    fprintf(as_file, mess, p1, p2, p3);
    fprintf(as_file, "\n");
  }
}

void COMMENT4 PROTO_N ((mess,p1,p2,p3,p4)) PROTO_T (char *mess X long p1 X long p2 X long p3 X long p4)
{
  if (do_comment)
  {
    fprintf(as_file, "## ");
    fprintf(as_file, mess, p1, p2, p3, p4);
    fprintf(as_file, "\n");
  }
}

#else				/* DO_COMMENT */

/* defined as null macros in comment.h */

#endif				/* DO_COMMENT */


void fail PROTO_N ((mess)) PROTO_T (char *mess)
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
