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


/* minix/diag_out.c */

/**********************************************************************
$Author: release $
$Date: 1998/03/27 09:47:50 $
$Revision: 1.2 $
$Log: diag_out.c,v $
 * Revision 1.2  1998/03/27  09:47:50  release
 * Changes for 4.1.2 release.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.12  1997/04/02  10:33:21  pwe
 * diagnose pl_tests
 *
 * Revision 1.11  1997/03/24  12:43:26  pwe
 * outn int->long
 *
 * Revision 1.10  1996/10/29  14:55:32  pwe
 * correct linux/elf stabs for global variables
 *
 * Revision 1.9  1996/07/05  09:07:43  pwe
 * correct stabs enums
 *
 * Revision 1.8  1996/05/09  17:30:47  pwe
 * shift invalidate_dest, and stabs postlude
 *
 * Revision 1.7  1996/04/19  16:14:16  pwe
 * simplified use of global id = id, correcting linux call problem
 *
 * Revision 1.6  1996/03/13  13:43:26  pwe
 * diags for long long
 *
 * Revision 1.5  1996/02/08  13:45:29  pwe
 * Linux elf v aout option
 *
 * Revision 1.4  1995/12/20  11:13:54  pwe
 * stabs local variable scopes
 *
 * Revision 1.3  1995/11/30  10:19:43  pwe
 * diag struct struct
 *
 * Revision 1.2  1995/03/28  14:28:53  pwe
 * correct diagnose empty file
 *
 * Revision 1.1  1995/03/17  18:29:52  pwe
 * stabs diagnostics for solaris and linux
 *
**********************************************************************/

#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "out.h"
#include "machine.h"
#include "shapemacs.h"
#include "expmacs.h"
#include "tags.h"
#include "szs_als.h"
#include "diagglob.h"
#include "xalloc.h"
#include "exp.h"
#include "mark_scope.h"
#include "externs.h"


/*
    OUTPUT INITIAL DIAGNOSTICS FOR A DIAGNOSE_TAG
*/

void output_diag
    PROTO_N ( (d, proc_no, e) )
    PROTO_T ( diag_info * d X int proc_no X exp e )
{
  UNUSED(d); UNUSED(proc_no); UNUSED(e);
  return;
}


/*
    OUTPUT FINAL DIAGNOSTICS FOR A DIAGNOSE_TAG
*/

void output_end_scope
    PROTO_N ( (d, e) )
    PROTO_T ( diag_info * d X exp e )
{
  UNUSED(d); UNUSED(e);
  return;
}


/*
    INITIALISE DIAGNOSTICS
*/

void out_diagnose_prelude
    PROTO_Z ()
{
  return;
}


/*
    INITIALIZE DIAGNOSTICS
*/

void init_stab_aux
    PROTO_Z ()
{
  return;
}

void out_diagnose_postlude
    PROTO_Z ()
{
  return;
}


/*
    OUTPUT DIAGNOSTICS FOR A GLOBAL VARIABLE
*/

void diag_val_begin
    PROTO_N ( (d, global, cname, pname) )
    PROTO_T ( diag_global * d X int global X int cname X char * pname )
{
  UNUSED(d); UNUSED(global); UNUSED(cname); UNUSED(pname);
  return;
}

void diag_val_end
    PROTO_N ( (d) )
    PROTO_T ( diag_global * d )
{
  UNUSED(d);
  return;
}


/*
    OUTPUT DIAGNOSTICS FOR A PROCEDURE
*/

void diag_proc_begin
    PROTO_N ( (d, global, cname, pname) )
    PROTO_T ( diag_global * d X int global X int cname X char * pname )
{
  UNUSED(d); UNUSED(global); UNUSED(cname); UNUSED(pname);
  return;
}

void diag_proc_end
    PROTO_N ( (d) )
    PROTO_T ( diag_global * d )
{
  UNUSED(d);
  return;
}
