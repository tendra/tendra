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
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: flags.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/10/23  09:24:18  pwe
 * extra diags
 *
 * Revision 1.3  1997/10/10  18:15:25  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.2  1997/02/18  12:56:24  currie
 * NEW DIAG STRUCTURE
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/



#include "config.h"
#include "common_types.h"
#include "flags.h"

int do_inlining = 1;		/* apply inlining optimisations */
int do_special_fns = 1;		/* replace special functions by tdf
				   equivalent operations */
int do_loopconsts = 1;		/* optimise constants in loops */
int do_foralls = 1;		/* do forall strength reductions */
int redo_structfns = 0;		/* reorganise proc calls delivering
				   structures */
int redo_structparams = 0;	/* reorganise proc calls with struct
				   parameters */
int diagnose = 0;		/* do diagnostics */
int do_profile = 0;		/* put in profiling code */
int do_alloca = 1;		/* inline alloca */
int all_variables_visible = 0;	/* set vis flag for all declarations */

int  double_align = 32;		/* alignment for 64 bit flpt */
int  stack_align = 32;		/* minimum alignment for stack */
int  param_align = 32;		/* minimum alignment for parameters */

int extra_checks = 1;		/* do some portability checks */
int separate_units = 0;		/* translate units separately */

int writable_strings = 0;	/* string are writable */

int round_after_flop = 0;	/* round after each floating point
				   operation */
int strict_fl_div = 1;		/* do not replace divisions by
				   multiplication by the inverse */

int PIC_code = 0;		/* produce PIC code */

int do_prom = 0;		/* produce PROM code (avoiding .data) */

#ifdef NEWDIAGS
int diag_visible = 0;		/* additional visibility if doing diagnostics */
int extra_diags = 0;		/* option for extended diagnostics */
#endif


