/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/



#include "config.h"
#include "common_types.h"
#include "flags.h"

int do_inlining = 1;		/* apply inlining optimisations */
int do_special_fns = 1;		/* replace special functions by tdf
							 *				   equivalent operations */
int do_loopconsts = 1;		/* optimise constants in loops */
int do_foralls = 1;		/* do forall strength reductions */
int redo_structfns = 0;		/* reorganise proc calls delivering
							 *				   structures */
int redo_structparams = 0;	/* reorganise proc calls with struct
							 *				   parameters */
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
							 *				   operation */
int strict_fl_div = 1;		/* do not replace divisions by
							 *				   multiplication by the inverse */

int PIC_code = 0;		/* produce PIC code */

int do_prom = 0;		/* produce PROM code (avoiding .data) */

#ifdef NEWDIAGS
int diag_visible = 0;		/* additional visibility if doing diagnostics */
int extra_diags = 0;		/* option for extended diagnostics */
#endif


