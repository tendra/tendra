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
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: labels.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/*   labels.c
	create and set program labels;
	The setting of a label clears all memory of the contents of
	the registers - see regexps.c
*/

#include "config.h"
#include "regexps.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "labels.h"

extern  FILE * as_file;

int   last_label = 31;

int new_label
    PROTO_Z ()
{
        last_label++;
  return last_label;
}

void set_label
    PROTO_N ( (l) )
    PROTO_T ( int l )
{
  clear_all ();
  if (as_file)
    fprintf (as_file, "$%d:\n", l);
  out_common (-l, ilabel);

}

void set_label_no_clear
    PROTO_N ( (l) )
    PROTO_T ( int l )
{
  if (as_file)
    fprintf (as_file, "$%d:\n", l);
  out_common (-l, ilabel);

}
