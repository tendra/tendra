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
#include "myassert.h"
#include "comment.h"
#include "proc.h"
#include "stack.h"
#include "parameter.h"
#include "error.h"
#include "installglob.h"
#include "dynamic_init.h"

void do__main_extern PROTO_Z ()
{
  fprintf(as_file,"\t.extern\t__main\n");
  fprintf(as_file,"\t.extern\t.__main\n");
}

void call__main PROTO_Z ()
{
  fprintf(as_file,"\tbl\t.__main\n");
  fprintf(as_file,"\tcror\t15,15,15\n");
}
int proc_is_main PROTO_N ((e)) PROTO_T (exp e)
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
