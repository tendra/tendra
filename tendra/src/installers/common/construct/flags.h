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
$Log: flags.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/10/23  09:24:21  pwe
 * extra diags
 *
 * Revision 1.3  1997/10/10  18:15:28  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.2  1997/02/18  12:56:24  currie
 * NEW DIAG STRUCTURE
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef flags_key
#define flags_key



#include "common_types.h"

extern  int do_inlining;
extern  int do_special_fns;
extern  int do_loopconsts;
extern  int do_foralls;
extern  int redo_structfns;
extern  int redo_structparams;
extern  int diagnose;
extern  int do_profile;
extern  int do_alloca;
extern  int double_align;
extern  int stack_align;
extern  int param_align;
extern  int extra_checks;
extern  int separate_units;
extern  int writable_strings;
extern  int PIC_code;
extern  int all_variables_visible;
extern  int round_after_flop;
extern  int strict_fl_div;
extern	int do_prom;

#ifdef NEWDIAGS
extern  int diag_visible;
extern  int extra_diags;
#endif


#endif



